/*
 * Copyright (c) 2000-2009, Eastman Kodak Company
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification,are permitted provided that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright notice, 
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the 
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Eastman Kodak Company nor the names of its 
 *       contributors may be used to endorse or promote products derived from 
 *       this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 * 
 *
 * Creation Date: 07/14/2001
 *
 * Original Author: 
 * Sam Fryer samuel.fryer@kodak.com 
 *
 * Contributor(s): 
 * 
 */ 
 
#include "ExifImageFile.h"
#include "ExifRawAppSeg.h"
#include "ExifImageFileIO.h"


ExifStatus ExifImageFile::writeImage( void )
{
    ExifStatus status = EXIF_OK ;

    // Make sure we have/want an APP1 segment
    ExifAppSegment* app1 = getAppSeg(0xFFE1,"Exif");
    if (app1 != NULL)
    {
        // Set the value of EXIFTAG_PIXELXDIMENSION and 
        // EXIFTAG_PIXELYDIMENSION
        // to match the value in the Jpeg Marker.
        ExifImageInfo info;
        if ( mImageModifiedOrCreated )
            mOutImage.getImageInfo(info);
        else
            getImageInfo( info );

        ExifTagEntry * tagEntry = new ExifTagEntryT<exif_uint32>
            (EXIFTAG_PIXELXDIMENSION,EXIF_LONG,1,info.width);
        setGenericTag(*tagEntry,EXIF_APP1_EXIFIFD);
        delete tagEntry ;
        tagEntry = new ExifTagEntryT<exif_uint32>
            (EXIFTAG_PIXELYDIMENSION,EXIF_LONG,1,info.height);
        setGenericTag(*tagEntry,EXIF_APP1_EXIFIFD);
        delete tagEntry ;
    }

    uint8* imgDataBuf = NULL ;
    exif_uint32 imgDataBufSize = 0 ;

    // Why are we separating the READWRITE case from the CREATE case?!?!?
    // Need to come back to this again to see.
    if ( mExifio->mode()&O_RDWR )
    {
        ExifIO *tmpExifio = NULL ;
        bool tmpExifioIsmExifio = false ;

        if( mTmpImageFile.size() == 0 )
        {
            // if we do not have a temporary file (new image) then we need
            // to get the image from the original file
            tmpExifio = mExifio ;
            tmpExifioIsmExifio = true ;  
        }
        else
        {
            tmpExifio = ExifIO::open( status, mTmpImageFile.c_str(), "r" );

            // We need to read in the App Segments of the temporary file
            // and insert them into our app seg manager because the app
            // might have written ICC Profiles to it. This functionality
            // should probably be implemented eventually as an App Segment
            // implementation. But we will do this for now.
            if ( status == EXIF_OK )
            {
                tmpExifio->flags() = mExifio->flags();
                readAppSegs(tmpExifio);
            }
        }

        if( tmpExifio )
        {
            exifoff_t offsetToDQT;
            getOffsetToDQT( tmpExifio, offsetToDQT ) ;
            tmpExifio->seek( offsetToDQT, SEEK_SET ) ;
            imgDataBufSize = tmpExifio->ioHandler().size() - offsetToDQT ;
            imgDataBuf = new uint8[imgDataBufSize] ;

            tmpExifio->read( imgDataBuf, imgDataBufSize ) ;

            if ( !tmpExifioIsmExifio )
            {
                tmpExifio->close() ;
                delete tmpExifio ;

                unlink( mTmpImageFile.c_str() ) ;
                mTmpImageFile = "";
            }
        }

        if ( status == EXIF_OK )
        {
            exif_uint32 tmpFlags = mExifio->flags();
            mExifio->close();
            delete mExifio ;
            mExifio = NULL ;
            mExifio = ExifIO::open( status, mFileName.c_str(), "w" ) ;
            if ( status == EXIF_OK )
            {
                mExifio->flags() = tmpFlags;
			    // Check the endianness of the current architechture
			    // HOST_BIGENDIAN is a configuration setting, true
			    // if native cpu byte order is big endian, false if little
			    bool bigendian = HOST_BIGENDIAN ;
			    initEndian( bigendian );
            }
        }
    }
    else
    {
        if ( mTmpImageFile.size() != 0 )
        {
            ExifIO *tmpExifio = ExifIO::open( status, mTmpImageFile.c_str(), "r" );
            if (tmpExifio)
            {
                tmpExifio->flags() = mExifio->flags();
                readAppSegs(tmpExifio);
                exifoff_t offsetToDQT;
                status = getOffsetToDQT( tmpExifio, offsetToDQT ) ;
				if (status == EXIF_OK)
				{
					tmpExifio->seek( offsetToDQT, SEEK_SET ) ;
					imgDataBufSize = tmpExifio->ioHandler().size() - offsetToDQT ;
					imgDataBuf = new uint8[imgDataBufSize] ;
					tmpExifio->read( imgDataBuf, imgDataBufSize ) ;
				}
                tmpExifio->close() ;
                delete tmpExifio ;
                unlink( mTmpImageFile.c_str() ) ;
                mTmpImageFile = "";
            }
        }
    }

    if ( status == EXIF_OK )
    {
        writeSOI() ;

        writeAppSegs() ;

        writeCom();
        
        if( !imgDataBuf )
        {
            status = EXIF_FILE_CLOSE_NO_IMAGE_ERROR;
        }
        else
        {
            // copy the image from memory to the file.
            mExifio->write( imgDataBuf, imgDataBufSize) ;
            delete [] imgDataBuf ;
        }
    }

    return status ;
}



ExifStatus ExifImageFile::writeAppSegs( void )
{
    std::vector<ExifAppSegment*> appSegs = mAppSegManager->getAllAppSegs(false) ;
    
    int numOfAppSegs = appSegs.size() ;
    
    for ( int i = 0; i < numOfAppSegs; i++ )
        appSegs[i]->write( mExifio ) ;

    return EXIF_OK;
}


ExifStatus ExifImageFile::writeCom( void )
{
    ExifStatus status = EXIF_OK ;
    unsigned int numOfCom = mComMarkerList.size() ;
    uint8 commark[] = { 0xFF, M_COM };
    tsize_t dataSize = 0;
    uint8 tagSize[2];
    for ( unsigned int i = 0; (i < numOfCom) && (status == EXIF_OK); i++ )
    {
        ExifComMarker * marker = mComMarkerList.getComMarker(i);
        uint8 * comdata = ( uint8 * )marker->getData(dataSize);
        if ((comdata != NULL) && 
            (mExifio->write((tdata_t)&commark[0],2*sizeof (uint8)) == 2*sizeof(uint8) ))
        {
            tsize_t tmpTagSize = dataSize+2;
            tagSize[1] = tmpTagSize & 0x000000FF;
            tagSize[0] = (tmpTagSize>>8) & 0x000000FF;
            if (mExifio->write((tdata_t)&tagSize[0],2*sizeof (uint8)) == 2*sizeof (uint8) )
            {
                if( mExifio->write((tdata_t)comdata,dataSize) != dataSize )
                {
                    status =  EXIF_FILE_WRITE_ERROR ;
                }
            }
            else
                status =  EXIF_FILE_WRITE_ERROR ;
        }
        else
            status =  EXIF_FILE_WRITE_ERROR ;
    }
    return status;
}


ExifStatus ExifImageFile::writeSOI( void )
{
    uint8 soi[] = { 0xFF, M_SOI };
    
    // No sense in writing the start of image if we are not
    // at the beginning of the file
    mExifio->seek( 0, SEEK_SET ) ;
    
    if( mExifio->write((tdata_t)&soi[0],2*sizeof (uint8)) != 2*sizeof(uint8) )
    {
        return EXIF_FILE_WRITE_ERROR ;
    }
    
    return EXIF_OK ;
}

