/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2012, assimp team

All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the following
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------
*/

/** @file  MSFSLoader.cpp
 *  @brief Implementation of the MSFS importer class
 */

#include "AssimpPCH.h"
#ifndef ASSIMP_BUILD_NO_MSFS_IMPORTER

// internal headers
#include "MSFSLoader.h"
#include "MSFSFileData.h"
#include "MSFSMDL2Parser.h"

using namespace Assimp;

static const aiImporterDesc desc = {
   "Microsoft Flight Simulator MDL Importer",
   "Thomas Sevaldrud",
   "",
   "",
   aiImporterFlags_SupportBinaryFlavour,
   0,
   0,
   0,
   0,
   "mdl"
};

// ------------------------------------------------------------------------------------------------
// Constructor to be privately used by Importer
MSFSLoader::MSFSLoader()
{
}

// ------------------------------------------------------------------------------------------------
// Destructor, private as well
MSFSLoader::~MSFSLoader()
{

}

// ------------------------------------------------------------------------------------------------
// Returns whether the class can handle the format of the given file.
bool MSFSLoader::CanRead(const std::string &pFile, IOSystem *pIOHandler, bool checkSig) const
{
   const std::string extension = GetExtension(pFile);

   // if check for extension is not enough, check for the magic tokens
   if (extension == "mdl" || !extension.length() || checkSig) {
      uint32_t tokens[2];
      tokens[0] = AI_MSFS_FOURCC_RIFF;
      return CheckMagicToken(pIOHandler,pFile,tokens,1,0);
   }
   return false;
}

void MSFSLoader::SetupProperties(const Importer *pImp)
{

}

const aiImporterDesc *MSFSLoader::GetInfo() const
{
   return &desc;
}

void MSFSLoader::InternReadFile(const std::string &pFile, aiScene *pScene, IOSystem *pIOHandler)
{
   boost::shared_ptr<IOStream> file( pIOHandler->Open( pFile, "rb"));

   // Check whether we can read from the file
   if( file.get() == NULL)
      throw DeadlyImportError( "Failed to open MSFS MDL file " + pFile + ".");

   boost::shared_ptr<StreamReaderLE> stream(new StreamReaderLE(file));

   MSFSMDL2Parser parser(stream);
   parser.parse(pScene);
}

#endif // !! ASSIMP_BUILD_NO_MSFS_IMPORTER
