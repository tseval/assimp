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

#include <iostream>
#include "BGLParser.h"

#include "AssimpPCH.h"

using namespace Assimp;
using namespace BGL;
using namespace std;

#ifdef DEBUG
#include <iostream>
#define DEBUGPRINT(x) std::cerr << x
#else
#define DEBUGPRINT(x)
#endif

//===========================================================================

BGLParser::BGLParser(boost::shared_ptr<StreamReaderLE> reader)
   : reader_(reader)
{
 done_       = false;
 unit_scale_ = 1.0;
 var_base32_ = 0;
}

//===========================================================================

BGLParser::BGLParser(StreamReaderLE *reader)
   : reader_(boost::shared_ptr<StreamReaderLE>(reader))
{
   done_       = false;
   unit_scale_ = 1.0;
   var_base32_ = 0;
}


//===========================================================================

BGLParser::~BGLParser()
{
}

//===========================================================================

void BGLParser::readBytes(char* buf, int count)
{
   for(int i = 0; i < count; i++)
      buf[i] = reader_->GetI1();
}

//===========================================================================

UNICOL BGLParser::readUNICOL()
{
   UNICOL color;
   // XXX: Why?!
   color.r = reader_->GetU1();
   color.a = reader_->GetU1();
   color.g = reader_->GetU1();
   color.b = reader_->GetU1();
   return color;
}

//===========================================================================

LLA BGLParser::readLLA()
{
   LLA lla;
   lla.lat = readSIF48();
   lla.lon = readAngl48();
   lla.alt = readSIF48();
   return lla;
}

//===========================================================================

SIF48 BGLParser::readSIF48()
{
   SIF48 val;
   //val.pad = stream_->GetU2();
   val.f = reader_->GetU2();
   val.i = reader_->GetU4();
   return val;
}

//===========================================================================

Angl48 BGLParser::readAngl48()
{
   Angl48 val;
   //val.pad = stream_->GetU2();
   val.lo = reader_->GetU2();
   val.hi = reader_->GetU4();
   return val;
}

//===========================================================================

XYZ16 BGLParser::readXYZ16()
{
   XYZ16 point;
   point.x = reader_->GetI2();
   point.y = reader_->GetI2();
   point.z = reader_->GetI2();
   return point;
}

//===========================================================================

XZ16 BGLParser::readXZ16()
{
   XZ16 point;
   point.x = reader_->GetI2();
   point.z = reader_->GetI2();
   return point;
}

//===========================================================================

PBH16 BGLParser::readPBH16()
{
   PBH16 pbh;
   pbh.pitch = reader_->GetI2();
   pbh.bank = reader_->GetI2();
   pbh.heading = reader_->GetI2();
   return pbh;
}

//===========================================================================

PXZ16 BGLParser::readPXZ16()
{
   PXZ16 pxz;
   pxz.p = reader_->GetU2();
   pxz.tx = reader_->GetI2();
   pxz.tz = reader_->GetI2();
   return pxz;
}

//===========================================================================

GVERTEX BGLParser::readGVERTEX()
{
   GVERTEX vtx;
   vtx.x = reader_->GetI2();
   vtx.y = reader_->GetI2();
   vtx.z = reader_->GetI2();
   vtx.nx = reader_->GetI2();
   vtx.ny = reader_->GetI2();
   vtx.nz = reader_->GetI2();
   return vtx;
}

//===========================================================================

VERTEX BGLParser::readVERTEX()
{
   VERTEX vtx;
   vtx.x = reader_->GetF4();
   vtx.y = reader_->GetF4();
   vtx.z = reader_->GetF4();
   vtx.nx = reader_->GetF4();
   vtx.ny = reader_->GetF4();
   vtx.nz = reader_->GetF4();
   vtx.tu = reader_->GetF4();
   vtx.tv = reader_->GetF4();
   return vtx;
}

//===========================================================================

MATERIAL BGLParser::readMATERIAL()
{
   MATERIAL mat;
   mat.diffuse_r = reader_->GetF4();
   mat.diffuse_g = reader_->GetF4();
   mat.diffuse_b = reader_->GetF4();
   mat.diffuse_a = reader_->GetF4();

   mat.ambient_r = reader_->GetF4();
   mat.ambient_g = reader_->GetF4();
   mat.ambient_b = reader_->GetF4();
   mat.ambient_a = reader_->GetF4();

   mat.specular_r = reader_->GetF4();
   mat.specular_g = reader_->GetF4();
   mat.specular_b = reader_->GetF4();
   mat.specular_a = reader_->GetF4();

   mat.emissive_r = reader_->GetF4();
   mat.emissive_g = reader_->GetF4();
   mat.emissive_b = reader_->GetF4();
   mat.emissive_a = reader_->GetF4();

   mat.power = reader_->GetF4();

   return mat;
}

//===========================================================================

TEXTURE BGLParser::readTEXTURE()
{
   TEXTURE tex;
   tex.cat = reader_->GetU4();
   tex.color = reader_->GetU4();
   tex.reserved = reader_->GetU4();
   tex.texture_size = reader_->GetF4();
   for(int i = 0; i < 64; i++)
      tex.tname[i] = reader_->GetU1();
   return tex;
}

//===========================================================================

XYZF32 BGLParser::readXYZF32()
{
   XYZF32 point;
   point.x = reader_->GetF4();
   point.y = reader_->GetF4();
   point.z = reader_->GetF4();
   return point;
}

//===========================================================================

GUid128 BGLParser::readGUID128()
{
   GUid128 guid128;
   for(int i = 0; i < 16; i++)
      guid128.guid[i] = reader_->GetU1();
   return guid128;
}


//===========================================================================

UInt32 BGLParser::readFourCC()
{
   char magic[4];
   readBytes(magic, 4);
   return AI_MAKE_MAGIC(magic);
}

//===========================================================================

void BGLParser::cvtFileString(const STRINGZ* name, STRINGZ* filename, int length)
{
 int j = 0;
 for(int i = 0; i < length; i++)
    {
    if(name[i] == '\0')
       break;
    if(!isspace(name[i]))
       filename[j++] = tolower(name[i]);
    }
 filename[j] = '\0';
}

//===========================================================================

void BGLParser::readStringZ(STRINGZ* str, int length)
{
 char c;
 int i = 0;
 while((c = reader_->GetU1()) != 0 && i < length - 1)
    str[i++] = c;
 str[i] = '\0';

 // Padding byte
 if((strlen((const char*)str) + 1) % 2)
    c = reader_->GetU1();
}

//===========================================================================

void BGLParser::callSub(long call)
{
 long addr = reader_->GetCurrentPos();
 stack_.push_front(addr);
 long dst = addr + call;
 reader_->SetCurrentPos(dst);
}

//===========================================================================

void BGLParser::jump(long jump)
{
 long addr = reader_->GetCurrentPos();
 long dst = addr + jump;
 reader_->SetCurrentPos(dst);
}

//===========================================================================

void BGLParser::parseOpcode(Enum16 opcode)
{
 long skip_offset = 0;

 switch(opcode)
    {
    case BGL_EOF:
       {
       BEOF(opcode);
       break;
       }

    case BGL_NOOP:
       {
       NOOP(opcode);
       break;
       }

    case BGL_CASE:
       {
       UInt16 number = reader_->GetU2();
       SInt16 token = reader_->GetI2();
       SInt16 fail_jump = reader_->GetI2();
       SInt16* jumps = new SInt16[number];
       for(int i = 0; i < number; i++)
          jumps[i] = reader_->GetI2();
       CASE(opcode, number, token, fail_jump, jumps);
       delete[] jumps;
       break;
       }

       /*
    case BGL_RESERVED:
       {
       RESERVED(opcode);
       break;
       }
       */

    case BGL_SURFACE:
       {
       SURFACE(opcode);
       break;
       }

    case BGL_SPNT:
       {
       XYZ16 point = readXYZ16();
       SPNT(opcode, point);
       break;
       }

    case BGL_CPNT:
       {
       XYZ16 point = readXYZ16();
       CPNT(opcode, point);
       break;
       }

    case BGL_CLOSURE:
       {
       CLOSURE(opcode);
       break;
       }

    case BGL_JUMP:
       {
       SInt16 jump = reader_->GetI2();
       JUMP(opcode, jump);
       break;
       }

    case BGL_DEFRES:
       {
       UInt16 index = reader_->GetU2();
       XYZ16 vertex = readXYZ16();
       DEFRES(opcode, index, vertex);
       break;
       }

    case BGL_STRRES:
       {
       UInt16 index = reader_->GetU2();
       STRRES(opcode, index);
       break;
       }

    case BGL_CNTRES:
       {
       UInt16 index = reader_->GetU2();
       CNTRES(opcode, index);
       break;
       }

    case BGL_SCOLOR:
       {
       UInt16 color= reader_->GetU2();
       SCOLOR(opcode, color);
       break;
       }

    case BGL_ELEVATION_MAP:
       {
       UInt16 grid_size_x = reader_->GetU2();
       UInt16 grid_size_z = reader_->GetU2();
       UInt16 square_size_x = reader_->GetU2();
       UInt16 square_size_z = reader_->GetU2();
       SInt16 starting_x = reader_->GetI2();
       SInt16 starting_z = reader_->GetI2();
       SInt16 min_altitude = reader_->GetI2();
       SInt16 max_altitude = reader_->GetI2();
       int size = 3*(grid_size_x+1)*(grid_size_z+1);
       SInt16* elevation_points = new SInt16[size];
       for(int i = 0; i < size; i++)
          elevation_points[i] = reader_->GetI2();
       ELEVATION_MAP(opcode, grid_size_x, grid_size_z, square_size_x, square_size_z, starting_x, starting_z, min_altitude, max_altitude, elevation_points);
       delete[] elevation_points;
       break;
       }

    case BGL_TEXTURE_ENABLE:
       {
       Bool16 onoff = reader_->GetU2();
       TEXTURE_ENABLE(opcode, onoff);
       break;
       }

    case BGL_TEXTURE:
       {
       UInt16 index = reader_->GetU2();
       SInt16 bias_x = reader_->GetI2();
       SInt16 free = reader_->GetI2();
       SInt16 bias_z = reader_->GetI2();
       STRINGZ name[14];
       readBytes(name, 14);
       STRINGZ filename[14];
       cvtFileString(name, filename, 14);
       TEXTURE1(opcode, index, bias_x, free, bias_z, filename);
       break;
       }

    case BGL_PALETTE:
       {
       STRINGZ name[14];
       readBytes(name, 14);
       STRINGZ filename[14];
       cvtFileString(name, filename, 14);
       PALETTE(opcode, filename);
       break;
       }

    case BGL_RESLIST:
       {
       UInt16 start_index = reader_->GetU2();
       UInt16 count = reader_->GetU2();
       XYZ16* vertex = new XYZ16[count];
       for(int i = 0; i < count; i++)
          vertex[i] = readXYZ16();
       RESLIST(opcode, start_index, count, vertex);
       delete[] vertex;
       break;
       }

    case BGL_IFIN_BOX_RAW_PLANE:
       {
       SInt16 fail = reader_->GetI2();
       XYZ16 center = readXYZ16();
       XYZ16 size = readXYZ16();
       PBH16 rotation = readPBH16();
       IFIN_BOX_RAW_PLANE(opcode, fail, center, size, rotation);
       break;
       }

    case BGL_IFIN2:
       {
       SInt16 fail = reader_->GetI2();
       Var16 var1 = reader_->GetU2();
       SInt16 low1 = reader_->GetI2();
       SInt16 high1 = reader_->GetI2();
       Var16 var2 = reader_->GetU2();
       SInt16 low2 = reader_->GetI2();
       SInt16 high2 = reader_->GetI2();
       IFIN2(opcode, fail, var1, low1, high1, var2, low2, high2);
       break;
       }

    case BGL_FACE:
       {
       UInt16 count = reader_->GetU2();
       XYZ16 point = readXYZ16();
       XYZ16 normal = readXYZ16();
       UInt16* vertices = new UInt16[count];
       for(int i = 0; i < count; i++)
          vertices[i] = reader_->GetU2();
       FACE(opcode, count, point, normal, vertices);
       delete[] vertices;
       break;
       }

    case BGL_HAZE:
       {
       UInt16 factor = reader_->GetU2();
       HAZE(opcode, factor);
       break;
       }

    case BGL_FACET_TMAP:
       {
       UInt16 count = reader_->GetU2();
       XYZ16 normal = readXYZ16();
       SInt32 dot_ref = reader_->GetI4();
       PXZ16* vertices = new PXZ16[count];
       for(int i = 0; i < count; i++)
          vertices[i] = readPXZ16();
       FACET_TMAP(opcode, count, normal, dot_ref, vertices);
       delete[] vertices;
       break;
       }

    case BGL_GFACET_TMAP:
       {
       UInt16 count = reader_->GetU2();
       XYZ16 normal = readXYZ16();
       SInt32 dot_ref = reader_->GetI4();
       PXZ16* vertices = new PXZ16[count];
       for(int i = 0; i < count; i++)
          vertices[i] = readPXZ16();
       GFACET_TMAP(opcode, count, normal, dot_ref, vertices);
       delete[] vertices;
       break;
       }

    case BGL_IFIN3:
       {
       SInt16 fail = reader_->GetI2();
       Var16 var1 = reader_->GetU2();
       SInt16 low1 = reader_->GetI2();
       SInt16 high1 = reader_->GetI2();
       Var16 var2 = reader_->GetU2();
       SInt16 low2 = reader_->GetI2();
       SInt16 high2 = reader_->GetI2();
       Var16 var3 = reader_->GetU2();
       SInt16 low3 = reader_->GetI2();
       SInt16 high3 = reader_->GetI2();
       IFIN3(opcode, fail, var1, low1, high1, var2, low2, high2, var3, low3, high3);
       break;
       }

    case BGL_RETURN:
       {
       RETURN(opcode);
       break;
       }

    case BGL_CALL:
       {
       SInt16 call = reader_->GetI2();
       CALL(opcode, call);
       break;
       }

    case BGL_IFIN1:
       {
       SInt16 fail = reader_->GetI2();
       Var16 var = reader_->GetU2();
       SInt16 low = reader_->GetI2();
       SInt16 high = reader_->GetI2();
       IFIN1(opcode, fail, var, low, high);
       break;
       }

    case BGL_SEPARATION_PLANE:
       {
       SInt16 alternate_jump = reader_->GetI2();
       XYZ16 normal = readXYZ16();
       SInt32 dot_ref = reader_->GetI4();
       SEPARATION_PLANE(opcode, alternate_jump, normal, dot_ref);
       break;
       }

    case BGL_SETWRD:
       {
       Var16 var1 = reader_->GetU2();
       SInt16 value = reader_->GetI2();
       SETWRD(opcode, var1, value);
       break;
       }

    case BGL_GRESLIST:
       {
       UInt16 start_index = reader_->GetU2();
       UInt16 count = reader_->GetU2();
       GVERTEX* vertex = new GVERTEX[count];
       for(int i = 0; i < count; i++)
          vertex[i] = readGVERTEX();
       GRESLIST(opcode, start_index, count, vertex);
       delete[] vertex;
       break;
       }

    case BGL_GFACET:
       {
       UInt16 count = reader_->GetU2();
       XYZ16 normal = readXYZ16();
       SInt32 dot_ref = reader_->GetI4();
       UInt16* vertices = new UInt16[count];
       for(int i = 0; i < count; i++)
          vertices[i] = reader_->GetU2();
       GFACET(opcode, count, normal, dot_ref, vertices);
       delete[] vertices;
       break;
       }

    case BGL_ADDOBJ32:
       {
       SInt32 call = reader_->GetI4();
       ADDOBJ32(opcode, call);
       break;
       }

    case BGL_REJECT:
       {
       SInt16 fail = reader_->GetI2();
       XYZ16 center = readXYZ16();
       UInt16 radius = reader_->GetU2();
       REJECT(opcode, fail, center, radius);
       break;
       }

    case BGL_SCOLOR24:
       {
       UNICOL color = readUNICOL();
       SCOLOR24(opcode, color);
       break;
       }

    case BGL_LCOLOR24:
       {
       UNICOL color = readUNICOL();
       LCOLOR24(opcode, color);
       break;
       }

    case BGL_SCALE:
       {
       SInt16 fail = reader_->GetI2();
       UInt16 range = reader_->GetU2();
       UInt16 size = reader_->GetU2();
       Var16 index = reader_->GetU2();
       UInt32 scale = reader_->GetU4();
       LLA lla = readLLA();
       SCALE(opcode, fail, range, size, index, scale, lla);
       break;
       }

    case BGL_RESROW:
       {
       UInt16 start_index = reader_->GetU2();
       UInt16 count = reader_->GetU2();
       XYZ16 starting_point = readXYZ16();
       XYZ16 ending_point = readXYZ16();
       RESROW(opcode, start_index, count, starting_point, ending_point);
       break;
       }

    case BGL_ADDOBJ:
       {
       SInt16 call = reader_->GetI2();
       ADDOBJ(opcode, call);
       break;
       }

    case BGL_INSTANCE:
       {
       SInt16 call = reader_->GetI2();
       PBH16 rotation = readPBH16();
       INSTANCE(opcode, call, rotation);
       break;
       }

    case BGL_SUPER_SCALE:
       {
       SInt16 fail = reader_->GetI2();
       UInt16 range = reader_->GetU2();
       UInt16 size = reader_->GetU2();
       UInt16 super_scale = reader_->GetU2();
       SUPER_SCALE(opcode, fail, range, size, super_scale);
       break;
       }

    case BGL_PNTROW:
       {
       XYZ16 starting_point = readXYZ16();
       XYZ16 ending_point = readXYZ16();
       UInt16 count = reader_->GetU2();
       PNTROW(opcode, starting_point, ending_point, count);
       break;
       }

    case BGL_POINT:
       {
       XYZ16 point = readXYZ16();
       POINT(opcode, point);
       break;
       }

    case BGL_CONCAVE:
       {
       CONCAVE(opcode);
       break;
       }

    case BGL_IFMSK:
       {
       SInt16 fail = reader_->GetI2();
       Var16 var = reader_->GetU2();
       Var16 mask = reader_->GetU2();
       IFMSK(opcode, fail, var, mask);
       break;
       }

    case BGL_VPOSITION:
       {
       SInt16 fail = reader_->GetI2();
       UInt16 range = reader_->GetU2();
       UInt16 size = reader_->GetU2();
       Var16 index = reader_->GetU2();
       Var16 var = reader_->GetU2();
       VPOSITION(opcode, fail, range, size, index, var);
       break;
       }

    case BGL_VINSTANCE:
       {
       SInt16 call = reader_->GetI2();
       Var16 var = reader_->GetU2();
       VINSTANCE(opcode, call, var);
       break;
       }

    case BGL_POSITION:
       {
       SInt16 fail = reader_->GetI2();
       UInt16 range = reader_->GetU2();
       UInt16 size = reader_->GetU2();
       Var16 index = reader_->GetU2();
       LLA lla = readLLA();
       POSITION(opcode, fail, range, size, index, lla);
       break;
       }

    case BGL_SEED:
       {
       SEED(opcode);
       break;
       }

    case BGL_FACET:
       {
       UInt16 count = reader_->GetU2();
       XYZ16 normal = readXYZ16();
       SInt32 dot_ref = reader_->GetI4();
       UInt16* vertices = new UInt16[count];
       for(int i = 0; i < count; i++)
          vertices[i] = reader_->GetU2();
       FACET(opcode, count, normal, dot_ref, vertices);
       delete[] vertices;
       break;
       }

    case BGL_SHADOW_CALL:
       {
       SInt16 call = reader_->GetI2();
       SHADOW_CALL(opcode, call);
       break;
       }

    case BGL_SHADOW_VPOSITION:
       {
       SInt16 fail = reader_->GetI2();
       UInt16 range = reader_->GetU2();
       UInt16 size = reader_->GetU2();
       Var16 index = reader_->GetU2();
       Var16 vlla = reader_->GetU2();
       SHADOW_VPOSITION(opcode, fail, range, size, index, vlla);
       break;
       }

    case BGL_SHADOW_VICALL:
       {
       SInt16 call = reader_->GetI2();
       Var16 vpbh = reader_->GetU2();
       SHADOW_VICALL(opcode, call, vpbh);
       break;
       }

    case BGL_POLYGON_RUNWAY:
       {
       LLA center = readLLA();
       Angl16 heading = reader_->GetU2();
       UInt16 length = reader_->GetU2();
       UInt16 width = reader_->GetU2();
       Flags8 flags = reader_->GetU1();
       Flags8 identifiers = reader_->GetU1();
       Flags8 surface_lights = reader_->GetU1();
       Flags8 specials = reader_->GetU1();
       Enum8 surface_type = reader_->GetU1();
       Flags8 threshold_flags = reader_->GetU1();
       UInt16 base_threshold = reader_->GetU2();
       UInt16 base_blast_pad = reader_->GetU2();
       UInt16 recip_threshold = reader_->GetU2();
       UInt16 recip_blast_pad = reader_->GetU2();
       Flags8 base_app_flags = reader_->GetU1();
       Enum8 base_app_system = reader_->GetU1();
       Enum8 base_app_strobes = reader_->GetU1();
       Flags8 base_vasi_system = reader_->GetU1();
       Angl16 base_vasi_angle = reader_->GetU2();
       SInt16 base_vasi_x = reader_->GetI2();
       SInt16 base_vasi_z = reader_->GetI2();
       SInt16 base_vasi_spacing = reader_->GetI2();
       Flags8 recip_app_flags = reader_->GetU1();
       Enum8 recip_app_system = reader_->GetU1();
       Enum8 recip_app_strobes = reader_->GetU1();
       Flags8 recip_vasi_system = reader_->GetU1();
       Angl16 recip_vasi_angle = reader_->GetU2();
       SInt16 recip_vasi_x = reader_->GetI2();
       SInt16 recip_vasi_z = reader_->GetI2();
       SInt16 recip_vasi_spacing = reader_->GetI2();
       POLYGON_RUNWAY(opcode, center, heading, length, width, flags, identifiers, surface_lights, specials, surface_type, threshold_flags, base_threshold, base_blast_pad, recip_threshold, recip_blast_pad, base_app_flags, base_app_system, base_app_strobes, base_vasi_system, base_vasi_angle, base_vasi_x, base_vasi_z, base_vasi_spacing, recip_app_flags, recip_app_system, recip_app_strobes, recip_vasi_system, recip_vasi_angle, recip_vasi_x, recip_vasi_z, recip_vasi_spacing);
       break;
       }

    case BGL_TEXTURE2:
       {
       UInt16 length = reader_->GetU2();
       UInt16 index = reader_->GetU2();
       Flags8 characteristics = reader_->GetU1();
       UInt8 checksum = reader_->GetU1();
       UNICOL color = readUNICOL();

       STRINGZ name[128];
       readStringZ(name, 128);
       STRINGZ filename[128];
       cvtFileString(name, filename, 128);
       TEXTURE2(opcode, length, index, characteristics, checksum, color, filename);
       break;
       }

    case BGL_TEXTURE_RUNWAY:
       {
       LLA center = readLLA();
       Angl16 heading = reader_->GetU2();
       UInt16 length = reader_->GetU2();
       UInt16 width = reader_->GetU2();
       Flags8 flags = reader_->GetU1();
       Flags8 identifiers = reader_->GetU1();
       Flags8 surface_lights = reader_->GetU1();
       Flags8 specials = reader_->GetU1();
       Enum8 surface_type = reader_->GetU1();
       Flags8 threshold_flags = reader_->GetU1();
       UInt16 base_threshold = reader_->GetU2();
       UInt16 base_blast_pad = reader_->GetU2();
       UInt16 recip_threshold = reader_->GetU2();
       UInt16 recip_blast_pad = reader_->GetU2();
       Flags8 base_app_flags = reader_->GetU1();
       Enum8 base_app_system = reader_->GetU1();
       Enum8 base_app_strobes = reader_->GetU1();
       Flags8 base_vasi_system = reader_->GetU1();
       Angl16 base_vasi_angle = reader_->GetU2();
       SInt16 base_vasi_x = reader_->GetI2();
       SInt16 base_vasi_z = reader_->GetI2();
       SInt16 base_vasi_spacing = reader_->GetI2();
       Flags8 recip_app_flags = reader_->GetU1();
       Enum8 recip_app_system = reader_->GetU1();
       Enum8 recip_app_strobes = reader_->GetU1();
       Flags8 recip_vasi_system = reader_->GetU1();
       Angl16 recip_vasi_angle = reader_->GetU2();
       SInt16 recip_vasi_x = reader_->GetI2();
       SInt16 recip_vasi_z = reader_->GetI2();
       SInt16 recip_vasi_spacing = reader_->GetI2();
       TEXTURE_RUNWAY(opcode, center, heading, length, width, flags, identifiers, surface_lights, specials, surface_type, threshold_flags, base_threshold, base_blast_pad, recip_threshold, recip_blast_pad, base_app_flags, base_app_system, base_app_strobes, base_vasi_system, base_vasi_angle, base_vasi_x, base_vasi_z, base_vasi_spacing, recip_app_flags, recip_app_system, recip_app_strobes, recip_vasi_system, recip_vasi_angle, recip_vasi_x, recip_vasi_z, recip_vasi_spacing);
       break;
       }

    case BGL_POINT_VICALL:
       {
       SInt16 call = reader_->GetI2();
       XYZ16 offset = readXYZ16();
       Angl16 pitch = reader_->GetU2();
       SInt16 vpitch = reader_->GetI2();
       Angl16 bank = reader_->GetU2();
       SInt16 vbank = reader_->GetI2();
       Angl16 heading = reader_->GetU2();
       SInt16 vheading = reader_->GetI2();
       POINT_VICALL(opcode, call, offset, pitch, vpitch, bank, vbank, heading, vheading);
       break;
       }

    case BGL_Var_SEG:
       {
       UInt16 dummy = reader_->GetU2();
       Var_SEG(opcode, dummy);
       break;
       }

    case BGL_BUILDING:
       {
       Flags16 info = reader_->GetU2();
       Flags16 codes = reader_->GetU2();
       XYZ16 offset = readXYZ16();
       UInt16 stories = reader_->GetU2();
       UInt16 size_x = reader_->GetU2();
       UInt16 size_z = reader_->GetU2();
       BUILDING(opcode, info, codes, offset, stories, size_x, size_z);
       break;
       }

    case BGL_VSCALE:
       {
       SInt16 fail = reader_->GetI2();
       UInt16 range = reader_->GetU2();
       UInt16 size = reader_->GetU2();
       Var16 index = reader_->GetU2();
       UInt32 scale = reader_->GetU4();
       SInt16 vlla = reader_->GetI2();
       VSCALE(opcode, fail, range, size, index, scale, vlla);
       break;
       }

    case BGL_MOVE_L2G:
       {
       UInt16 global = reader_->GetU2();
       SInt16 local = reader_->GetI2();
       MOVE_L2G(opcode, global, local);
       break;
       }

    case BGL_MOVE_G2L:
       {
       SInt16 local = reader_->GetI2();
       UInt16 global = reader_->GetU2();
       MOVE_G2L(opcode, local, global);
       break;
       }

    case BGL_MOVEWORD:
       {
       SInt16 to = reader_->GetI2();
       SInt16 from = reader_->GetI2();
       MOVEWORD(opcode, to, from);
       break;
       }

    case BGL_GCOLOR:
       {
       Var16 color = reader_->GetU2();
       GCOLOR(opcode, color);
       break;
       }

    case BGL_NEW_LCOLOR:
       {
       Var16 color = reader_->GetU2();
       NEW_LCOLOR(opcode, color);
       break;
       }

    case BGL_NEW_SCOLOR:
       {
       Var16 color = reader_->GetU2();
       NEW_SCOLOR(opcode, color);
       break;
       }

    case BGL_SURFACE_TYPE:
       {
       Enum8 surface_type = reader_->GetU1();
       Enum8 surface_condition = reader_->GetU1();
       UInt16 size_x = reader_->GetU2();
       UInt16 size_z = reader_->GetU2();
       UInt16 altitude = reader_->GetU2();
       SURFACE_TYPE(opcode, surface_type, surface_condition, size_x, size_z, altitude);
       break;
       }

    case BGL_SET_WEATHER:
       {
       UInt16 length = reader_->GetU2();
       SET_WEATHER(opcode, length);
       break;
       }

    case BGL_WEATHER:
       {
       Enum8 fixed = reader_->GetU1();
       Enum8 type = reader_->GetU1();
       Angl16 heading = reader_->GetU2();
       UInt16 scalar = reader_->GetU2();
       UInt16 extra = reader_->GetU2();
       WEATHER(opcode, fixed, type, heading, scalar, extra);
       break;
       }

    case BGL_TEXTURE_BOUNDS:
       {
       UInt32 lower_x = reader_->GetU4();
       UInt32 lower_z = reader_->GetU4();
       UInt32 upper_x = reader_->GetU4();
       UInt32 upper_z = reader_->GetU4();
       TEXTURE_BOUNDS(opcode, lower_x, lower_z, upper_x, upper_z);
       break;
       }

    case BGL_TEXTURE_REPEAT:
       {
       SInt16 bias_x = reader_->GetI2();
       SInt16 free = reader_->GetI2();
       SInt16 bias_z = reader_->GetI2();
       TEXTURE_REPEAT(opcode, bias_x, free, bias_z);
       break;
       }

    case BGL_IFSIZEV:
       {
       SInt16 smaller = reader_->GetI2();
       UInt16 real_size = reader_->GetU2();
       UInt16 pixels_ref = reader_->GetU2();
       IFSIZEV(opcode, smaller, real_size, pixels_ref);
       break;
       }

    case BGL_FACE_TMAP:
       {
       UInt16 count = reader_->GetU2();
       XYZ16 point = readXYZ16();
       XYZ16 normal = readXYZ16();
       PXZ16* vertices = new PXZ16[count];
       for(int i = 0; i < count; i++)
          vertices[i] = readPXZ16();
       FACE_TMAP(opcode, count, point, normal, vertices);
       delete[] vertices;
       break;
       }

    case BGL_IFVIS:
       {
       SInt16 off_screen = reader_->GetI2();
       UInt16 count = reader_->GetU2();
       UInt16* points = new UInt16[count];
       for(int i = 0; i < count; i++)
          points[i] = reader_->GetU2();
       IFVIS(opcode, off_screen, count, points);
       delete[] points;
       break;
       }

    case BGL_LIBRARY_CALL:
       {
       UInt16 index = reader_->GetU2();
       GUid128 library_id = readGUID128();
       LIBRARY_CALL(opcode, index, library_id);
       break;
       }

    case BGL_LIST:
       {
       SInt16 total_size = reader_->GetI2();
       UInt16 count = reader_->GetU2();
       // XXX: Uncertain here. The original code simply read a single pointer value
       // four bytes instead of the entire array. This opcode is not much in use
       // though...
       UInt16* indexes = new UInt16[count];
       for(int i = 0; i < count; i++)
          indexes[i] = reader_->GetU2();
       LIST(opcode, total_size, count, indexes);
       delete[] indexes;
       break;
       }

    case BGL_VSCOLOR:
       {
       Var16 vcolor = reader_->GetU2();
       VSCOLOR(opcode, vcolor);
       break;
       }

    case BGL_VGCOLOR:
       {
       Var16 vcolor = reader_->GetU2();
       VGCOLOR(opcode, vcolor);
       break;
       }

    case BGL_VLCOLOR:
       {
       Var16 vcolor = reader_->GetU2();
       VLCOLOR(opcode, vcolor);
       break;
       }

    case BGL_ROAD_START:
       {
       UInt16 width = reader_->GetU2();
       XYZ16 point = readXYZ16();
       ROAD_START(opcode, width, point);
       break;
       }

    case BGL_ROAD_CONT:
       {
       XYZ16 point = readXYZ16();
       ROAD_CONT(opcode, point);
       break;
       }

    case BGL_RIVER_START:
       {
       UInt16 width = reader_->GetU2();
       XYZ16 point = readXYZ16();
       RIVER_START(opcode, width, point);
       break;
       }

    case BGL_RIVER_CONT:
       {
       XYZ16 point = readXYZ16();
       RIVER_CONT(opcode, point);
       break;
       }

    case BGL_IFSIZEH:
       {
       SInt16 smaller = reader_->GetI2();
       UInt16 real_size = reader_->GetU2();
       UInt16 pixels_ref = reader_->GetU2();
       IFSIZEH(opcode, smaller, real_size, pixels_ref);
       break;
       }

    case BGL_TAXIWAY_START:
       {
       UInt16 width = reader_->GetU2();
       XYZ16 point = readXYZ16();
       TAXIWAY_START(opcode, width, point);
       break;
       }

    case BGL_TAXIWAY_CONT:
       {
       XYZ16 point = readXYZ16();
       TAXIWAY_CONT(opcode, point);
       break;
       }

    case BGL_AREA_SENSE:
       {
       SInt16 outside = reader_->GetI2();
       UInt16 count = reader_->GetU2();
       // XXX: Uncertain. Original code only read a pointer value
       XZ16* point = new XZ16[count];
       for(int i = 0; i < count; i++)
          point[i] = readXZ16();
       AREA_SENSE(opcode, outside, count, point);
       delete[] point;
       break;
       }

    case BGL_ALTITUDE_SET:
       {
       SInt16 altitude = reader_->GetI2();
       ALTITUDE_SET(opcode, altitude);
       break;
       }

    case BGL_IFINBOXP:
       {
       SInt16 outside = reader_->GetI2();
       SInt16 low_x = reader_->GetI2();
       SInt16 high_x = reader_->GetI2();
       SInt16 low_y = reader_->GetI2();
       SInt16 high_y = reader_->GetI2();
       SInt16 low_z = reader_->GetI2();
       SInt16 high_z = reader_->GetI2();
       IFINBOXP(opcode, outside, low_x, high_x, low_y, high_y, low_z, high_z);
       break;
       }

    case BGL_ADDCAT:
       {
       SInt16 call = reader_->GetI2();
       Enum16 category = reader_->GetU2();
       ADDCAT(opcode, call, category);
       break;
       }

    case BGL_ADDMNT:
       {
       SInt16 call = reader_->GetI2();
       ADDMNT(opcode, call);
       break;
       }

    case BGL_BGL:
       {
       BGL(opcode);
       break;
       }

    case BGL_SCALE_AGL:
       {
       SInt16 fail = reader_->GetI2();
       UInt16 range = reader_->GetU2();
       UInt16 size = reader_->GetU2();
       Var16 index = reader_->GetU2();
       UInt32 scale = reader_->GetU4();
       LLA lla = readLLA();

       SCALE_AGL(opcode, fail, range, size, index, scale, lla);
       break;
       }

    case BGL_ROAD_CONTW:
       {
       UInt16 width = reader_->GetU2();
       XYZ16 point = readXYZ16();
       ROAD_CONTW(opcode, width, point);
       break;
       }

    case BGL_RIVER_CONTW:
       {
       UInt16 width = reader_->GetU2();
       XYZ16 point = readXYZ16();
       RIVER_CONTW(opcode, width, point);
       break;
       }

    case BGL_SELECT:
       {
       SInt16 vindex = reader_->GetI2();
       UInt16 shift_mask = reader_->GetU2();
       SInt32 list = reader_->GetI4();
       SELECT(opcode, vindex, shift_mask, list);
       break;
       }

    case BGL_PERSPECTIVE:
       {
       PERSPECTIVE(opcode);
       break;
       }

    case BGL_SETWRD_GLOBAL:
       {
       Enum16 gindex = reader_->GetU2();
       SInt16 value = reader_->GetI2();
       SETWRD_GLOBAL(opcode, gindex, value);
       break;
       }

    case BGL_RESPNT:
       {
       Enum16 pindex = reader_->GetU2();
       RESPNT(opcode, pindex);
       break;
       }

    case BGL_RESCALE:
       {
       SInt16 fail = reader_->GetI2();
       UInt16 range = reader_->GetU2();
       UInt16 size = reader_->GetU2();
       UInt32 scale = reader_->GetU4();
       RESCALE(opcode, fail, range, size, scale);
       break;
       }

    case BGL_FIXED_COLORS:
       {
       UInt16 count = reader_->GetU2();
       FIXED_COLORS(opcode, count);
       break;
       }

    case BGL_JUMP32:
       {
       SInt32 jump = reader_->GetI4();
       JUMP32(opcode, jump);
       break;
       }

    case BGL_Var_BASE32:
       {
       Var32 address = reader_->GetU4();
       Var_BASE32(opcode, address);
       break;
       }

    case BGL_CALL32:
       {
       SInt32 call = reader_->GetI4();
       CALL32(opcode, call);
       break;
       }

    case BGL_ADDCAT32:
       {
       SInt32 call = reader_->GetI4();
       Enum16 category = reader_->GetU2();
       ADDCAT32(opcode, call, category);
       break;
       }

    case BGL_VFILE_MARKER:
       {
       SInt16 offset = reader_->GetI2();
       VFILE_MARKER(opcode, offset);
       break;
       }

    case BGL_ALPHA:
       {
       UInt32 value = reader_->GetU4();
       ALPHA(opcode, value);
       break;
       }

    case BGL_TEXT:
       {
       XYZ16 start_point = readXYZ16();
       Var16 vtext = reader_->GetU2();
       Flags16 flags = reader_->GetU2();
       BTEXT(opcode, start_point, vtext, flags);
       break;
       }

    case BGL_CRASH:
       {
       UInt16 length = reader_->GetU2();
       UInt16 ground_radius = reader_->GetU2();
       SInt16 scale = reader_->GetI2();
       SInt16 instance = reader_->GetI2();
       Bool8 processed = reader_->GetU1();
       Enum8 density = reader_->GetU1();
       CRASH(opcode, length, ground_radius, scale, instance, processed, density);
       break;
       }

    case BGL_CRASH_INDIRECT:
       {
       SInt16 call = reader_->GetI2();
       SInt16 scale = reader_->GetI2();
       SInt16 instance = reader_->GetI2();
       Bool8 processed = reader_->GetU1();
       Enum8 density = reader_->GetU1();
       CRASH_INDIRECT(opcode, call, scale, instance, processed, density);
       break;
       }

    case BGL_CRASH_START:
       {
       UInt16 length = reader_->GetU2();
       UInt16 ground_radius = reader_->GetU2();
       CRASH_START(opcode, length, ground_radius);
       break;
       }

    case BGL_CRASH_SPHERE:
       {
       SInt16 outside = reader_->GetI2();
       UInt16 radius = reader_->GetU2();
       CRASH_SPHERE(opcode, outside, radius);
       break;
       }

    case BGL_CRASH_BOX:
       {
       SInt16 outside = reader_->GetI2();
       XYZ16 center_bias = readXYZ16();
       XYZ16 rectangle = readXYZ16();
       PBH16 pbh = readPBH16();
       CRASH_BOX(opcode, outside, center_bias, rectangle, pbh);
       break;
       }

    case BGL_SET_CRASH:
       {
       Enum16 type = reader_->GetU2();
       SET_CRASH(opcode, type);
       break;
       }

    case BGL_INTERPOLATE:
       {
       SInt32 vinput_base = reader_->GetI4();
       SInt16 vinput = reader_->GetI2();
       SInt32 voutput_base = reader_->GetI4();
       SInt16 voutput = reader_->GetI2();
       SInt32 vtable_base = reader_->GetI4();
       SInt16 vinput2 = reader_->GetI2();
       INTERPOLATE(opcode, vinput_base, vinput, voutput_base, voutput, vtable_base, vinput2);
       break;
       }

    case BGL_OVERRIDE:
       {
       SInt32 vbase = reader_->GetI4();
       OVERRIDE(opcode, vbase);
       break;
       }

    case BGL_OBJECT:
       {
       UInt16 total_length = reader_->GetU2();
       Enum16 category = reader_->GetU2();
       cerr << "BGL_OBJECT: length = " << total_length << ", Category = 0x" << hex << category << dec << endl;
       switch(category)
          {
       /*
          case BUILD_RECT_FLAT_ROOF_T:
             {
             BUILD_RECT_FLAT_ROOF_S build;
             read(&build, sizeof(BUILD_RECT_FLAT_ROOF_S), 1);
             BUILD_RECT_FLAT_ROOF(opcode, total_length, category, build);
             break;
             }

          case BUILD_RECT_RIDGE_ROOF_T:
             {
             BUILD_RECT_RIDGE_ROOF_S build;
             read(&build, sizeof(BUILD_RECT_RIDGE_ROOF_S), 1);
             BUILD_RECT_RIDGE_ROOF(opcode, total_length, category, build);
             break;
             }

          case BUILD_RECT_PEAK_ROOF_T:
             {
             BUILD_RECT_PEAK_ROOF_S build;
             read(&build, sizeof(BUILD_RECT_PEAK_ROOF_S), 1);
             BUILD_RECT_PEAK_ROOF(opcode, total_length, category, build);
             break;
             }

          case BUILD_RECT_SLANT_ROOF_T:
             {
             BUILD_RECT_SLANT_ROOF_S build;
             read(&build, sizeof(BUILD_RECT_SLANT_ROOF_S), 1);
             BUILD_RECT_SLANT_ROOF(opcode, total_length, category, build);
             break;
             }

          case BUILD_PYRAMID_T:
             {
             BUILD_PYRAMID_S build;
             read(&build, sizeof(BUILD_PYRAMID_S), 1);
             BUILD_PYRAMID(opcode, total_length, category, build);
             break;
             }

          case BUILD_N_SIDED_T:
          case BUILD_OCTAGONAL_T:
             {
             BUILD_MULTI_SIDED_S build;
             read(&build, sizeof(BUILD_MULTI_SIDED_S), 1);
             BUILD_MULTI_SIDED(opcode, total_length, category, build);
             break;
             }
*/
       // XXX: Implement these later if we want to parse BGL files in addition
       // to MDL
          default:
             cerr << "Unknown category: " << hex << category << dec << "!\n";
             reader_->IncPtr(total_length - 6);
             break;
          }
       break;
       }

    case BGL_VALPHA:
       {
       SInt16 variable = reader_->GetI2();
       VALPHA(opcode, variable);
       break;
       }

    case BGL_SPRITE_VICALL:
       {
       SInt16 call = reader_->GetI2();
       XYZ16 offset = readXYZ16();
       PBH16 pbh = readPBH16();
       SInt16 vpitch = reader_->GetI2();
       SInt16 vbank = reader_->GetI2();
       SInt16 vheading = reader_->GetI2();
       SPRITE_VICALL(opcode, call, offset, pbh, vpitch, vbank, vheading);
       break;
       }

    case BGL_TEXTURE_ROAD_START:
       {
       Enum16 style = reader_->GetU2();
       UInt16 width = reader_->GetU2();
       XYZ16 point = readXYZ16();
       TEXTURE_ROAD_START(opcode, style, width, point);
       break;
       }

    case BGL_IFIN_INSTANCED_BOX_PLANE:
       {
       SInt16 fail = reader_->GetI2();
       XYZ16 center = readXYZ16();
       XYZ16 size = readXYZ16();
       PBH16 rotation = readPBH16();
       IFIN_INSTANCED_BOX_PLANE(opcode, fail, center, size, rotation);
       break;
       }

    case BGL_NEW_RUNWAY:
       {
       UInt16 total_length = reader_->GetU2();
       NEW_RUNWAY(opcode, total_length);

       long rwy_end = reader_->GetCurrentPos() + total_length - 4;
       while(reader_->GetCurrentPos() < rwy_end)
          {
          Enum8 rwy_opcode = reader_->GetU1();
          switch (rwy_opcode)
             {
             case BGL_RWY_RUNWAY_BASE:
                {
                LLA lla = readLLA();
                Angl16 heading = reader_->GetU2();
                UInt16 length = reader_->GetU2();
                UInt16 width = reader_->GetU2();
                Flags16 markings = reader_->GetU2();
                Enum8 surface_type = reader_->GetU1();
                Flags8 surface_lights = reader_->GetU1();
                Flags8 identifiers = reader_->GetU1();
                RWY_RUNWAY_BASE(rwy_opcode, lla, heading, length, width, markings, surface_type, surface_lights, identifiers);
                break;
                }

             case BGL_RWY_BASE_THRESHOLD:
                {
                UInt8 spare = reader_->GetU1();
                UInt16 length = reader_->GetU2();
                RWY_BASE_THRESHOLD(rwy_opcode, spare, length);
                break;
                }

             case BGL_RWY_RECIP_THRESHOLD:
                {
                UInt8 spare = reader_->GetU1();
                UInt16 length = reader_->GetU2();
                RWY_RECIP_THRESHOLD(rwy_opcode, spare, length);
                break;
                }

             case BGL_RWY_BASE_BLAST_PAD:
                {
                UInt8 spare = reader_->GetU1();
                UInt16 length = reader_->GetU2();
                RWY_BASE_BLAST_PAD(rwy_opcode, spare, length);
                break;
                }

             case BGL_RWY_RECIP_BLAST_PAD:
                {
                UInt8 spare = reader_->GetU1();
                UInt16 length = reader_->GetU2();
                RWY_RECIP_BLAST_PAD(rwy_opcode, spare, length);
                break;
                }

             case BGL_RWY_BASE_APPROACH_LIGHTS:
                {
                UInt8 spare = reader_->GetU1();
                Flags8 flags = reader_->GetU1();
                Enum8 system = reader_->GetU1();
                Enum8 strobes = reader_->GetU1();
                Flags8 vasi_system = reader_->GetU1();
                Angl16 vasi_angle = reader_->GetU2();
                SInt16 vasi_x = reader_->GetI2();
                SInt16 vasi_z = reader_->GetI2();
                SInt16 vasi_spacing = reader_->GetI2();
                RWY_BASE_APPROACH_LIGHTS(rwy_opcode, spare, flags, system, strobes, vasi_system, vasi_angle, vasi_x, vasi_z, vasi_spacing);
                break;
                }

             case BGL_RWY_RECIP_APPROACH_LIGHTS:
                {
                UInt8 spare = reader_->GetU1();
                Flags8 flags = reader_->GetU1();
                Enum8 system = reader_->GetU1();
                Enum8 strobes = reader_->GetU1();
                Flags8 vasi_system = reader_->GetU1();
                Angl16 vasi_angle = reader_->GetU2();
                SInt16 vasi_x = reader_->GetI2();
                SInt16 vasi_z = reader_->GetI2();
                SInt16 vasi_spacing = reader_->GetI2();
                RWY_RECIP_APPROACH_LIGHTS(rwy_opcode, spare, flags, system, strobes, vasi_system, vasi_angle, vasi_x, vasi_z, vasi_spacing);
                break;
                }

             case BGL_RWY_BASE_OVERRUN:
                {
                Enum8 surface_type = reader_->GetU1();
                UInt16 length = reader_->GetU2();
                RWY_BASE_OVERRUN(rwy_opcode, surface_type, length);
                break;
                }

             case BGL_RWY_RECIP_OVERRUN:
                {
                Enum8 surface_type = reader_->GetU1();
                UInt16 length = reader_->GetU2();
                RWY_RECIP_OVERRUN(rwy_opcode, surface_type, length);
                break;
                }

             case BGL_RWY_BASE_DISTANCE_LEFT:
                {
                UInt8 info = reader_->GetU1();
                UInt16 x_offset = reader_->GetU2();
                RWY_BASE_DISTANCE_LEFT(rwy_opcode, info, x_offset);
                break;
                }

             case BGL_RWY_RECIP_DISTANCE_LEFT:
                {
                UInt8 info = reader_->GetU1();
                UInt16 x_offset = reader_->GetU2();
                RWY_RECIP_DISTANCE_LEFT(rwy_opcode, info, x_offset);
                break;
                }
             }
          }
       break;
       }

    case BGL_ZBIAS:
       {
       UInt16 zbias = reader_->GetU2();
       ZBIAS(opcode, zbias);
       break;
       }

    case BGL_ANIMATE:
       {
       SInt32 vinput_base = reader_->GetI4();
       SInt32 vinput = reader_->GetI4();
       SInt32 vtable_base = reader_->GetI4();
       SInt32 vinput2 = reader_->GetI4();
       Float32 x = reader_->GetF4();
       Float32 y = reader_->GetF4();
       Float32 z = reader_->GetF4();
       ANIMATE(opcode, vinput_base, vinput, vtable_base, vinput2, x, y, z);
       break;
       }

    case BGL_TRANSFORM_END:
       {
       TRANSFORM_END(opcode);
       break;
       }

    case BGL_TRANSFORM_MATRIX:
       {
       XYZF32 values = readXYZF32();
       Float32 q00 = reader_->GetF4();
       Float32 q01 = reader_->GetF4();
       Float32 q02 = reader_->GetF4();
       Float32 q10 = reader_->GetF4();
       Float32 q11 = reader_->GetF4();
       Float32 q12 = reader_->GetF4();
       Float32 q20 = reader_->GetF4();
       Float32 q21 = reader_->GetF4();
       Float32 q22 = reader_->GetF4();
       TRANSFORM_MATRIX(opcode, values, q00, q01, q02, q10, q11, q12, q20, q21, q22);
       break;
       }

    case BGL_LIGHT:
       {
       Enum16 light_type = reader_->GetU2();
       XYZF32 location = readXYZF32();
       UInt32 intensity = reader_->GetU4();
       Float32 reserved = reader_->GetF4();
       Float32 reserved2 = reader_->GetF4();
       UNICOL color = readUNICOL();
       XYZF32 reserved3 = readXYZF32();
       LIGHT(opcode, light_type, location, intensity, reserved, reserved2, color, reserved3);
       break;
       }

    case BGL_IFINF1:
       {
       /* According to spec it should be 16-bits offset, but
        * 32-bits seems more likely!
        */
       //SInt16 fail = stream_->GetI2();
       //read(&fail, sizeof(SInt16), 1);
       SInt32 fail = reader_->GetI4();
       Var16 var = reader_->GetU2();
       Float32 low = reader_->GetF4();
       Float32 high = reader_->GetF4();
       IFINF1(opcode, fail, var, low, high);
       break;
       }

    case BGL_TEXTURE_SIZE:
       {
       Float32 size = reader_->GetF4();
       TEXTURE_SIZE(opcode, size);
       break;
       }

    case BGL_VERTEX_LIST:
       {
       UInt16 count = reader_->GetU2();
       UInt32 reserved = reader_->GetU4();
       VERTEX* vertex = new VERTEX[count];
       for(int i = 0; i < count; i++)
          vertex[i] = readVERTEX();
       VERTEX_LIST(opcode, count, reserved, vertex);
       delete vertex;
       break;
       };

    case BGL_MATERIAL_LIST:
       {
       UInt16 count = reader_->GetU2();
       UInt32 reserved = reader_->GetU4();
       MATERIAL* material = new MATERIAL[count];
       for(int i = 0; i < count; i++)
          material[i] = readMATERIAL();
       MATERIAL_LIST(opcode, count, reserved, material);
       delete material;
       break;
       };

    case BGL_TEXTURE_LIST:
       {
       UInt16 count = reader_->GetU2();
       UInt32 reserved = reader_->GetU4();
       TEXTURE* texture = new TEXTURE[count];
       for(int i = 0; i < count; i++)
          texture[i] = readTEXTURE();
       TEXTURE_LIST(opcode, count, reserved, texture);
       delete texture;
       break;
       };

    case BGL_MOUSERECT_LIST:
       {
       UInt16 count = reader_->GetU2();
       skip_offset = count*11*4;
//       cerr << "BGL_MOUSERECT_LIST: count = " << count << endl;
       break;
       };

    case BGL_SET_MOUSERECT:
       {
       UInt16 index = reader_->GetU2();
//       cerr << "BGL_SET_MOUSERECT: idx = " << index << endl;
       break;
       }

    case BGL_TAG:
       {
//       cerr << "BGL_TAG addr = " << (int)ftell(fp_) << endl;
       STRINGZ name[16];
       for(int i = 0; i < 16; i++)
          name[i] = reader_->GetU1();
       }

    case BGL_SET_MATERIAL:
       {
       UInt16 material_index = reader_->GetU2();
       UInt16 texture_index  = reader_->GetU2();
       SET_MATERIAL(opcode, material_index, texture_index);
       break;
       }

    case BGL_DRAW_TRIAnglE_LIST:
       {
       UInt16 vertex_start = reader_->GetU2();
       UInt16 vertex_count = reader_->GetU2();
       UInt16 index_count = reader_->GetU2();
       UInt16* index_list = new UInt16[index_count];
       for(int i = 0; i < index_count; i++)
          index_list[i] = reader_->GetU2();
       DRAW_TRIAnglE_LIST(opcode, vertex_start, vertex_count, index_count, index_list);
       delete[] index_list;
       break;
       }

    case BGL_DRAW_LINE_LIST:
       {
       UInt16 vertex_start = reader_->GetU2();
       UInt16 vertex_count = reader_->GetU2();
       UInt16 index_count = reader_->GetU2();
       UInt16* index_list = new UInt16[index_count];
       for(int i = 0; i < index_count; i++)
          index_list[i] = reader_->GetU2();
       DRAW_LINE_LIST(opcode, vertex_start, vertex_count, index_count, index_list);
       delete[] index_list;
       break;
       }

    case BGL_DRAW_POINT_LIST:
       {
       UInt16 vertex_start = reader_->GetU2();
       UInt16 vertex_count = reader_->GetU2();
       UInt16 index_count = reader_->GetU2();
       UInt16* index_list = new UInt16[index_count];
       for(int i = 0; i < index_count; i++)
          index_list[i] = reader_->GetU2();
       DRAW_POINT_LIST(opcode, vertex_start, vertex_count, index_count, index_list);
       delete[] index_list;
       break;
       }

    case BGL_BEGIN:
       {
       UInt32 version = reader_->GetU4();
       BEGIN(opcode, version);
       break;
       }

    case BGL_END:
       {
       END(opcode);
       break;
       }

       /*
    case 0x04:
       {
       SInt16 v1, v2, v3, v4;
       read(&v1, sizeof(SInt16), 1);
       read(&v2, sizeof(SInt16), 1);
       read(&v3, sizeof(SInt16), 1);
       read(&v4, sizeof(SInt16), 1);
       cerr << "RESERVED 0x04: " << v1 << ", " << v2 << ", " << v3 << ", " << v4 << endl;
       break;
       }
       */

       /*
    case 0x81:
       {
       cerr << "SHADOW_POSITION (0x81)\n";
       LLA lla;
       readLLA(lla);
       DEBUGPRINT("  lla	 = " << lla << endl);
       break;
       }
       */
       /*
    case 0xBF:
       {
       cerr << "0xBF:\n";

//       UInt16 size;
//       read(&size, sizeof(UInt16), 1);

       for(int l = 0; l < 8; l++)
          {
          for(int i = 0; i < 16; i++)
             {
             unsigned char b;
             read(&b, 1, 1);
             fprintf(stderr, "%02x ", b);
             }
          cerr << endl;
          }
       break;
       }
       */

    default: // Unknown opcode
       {
       if (opcode < 256)
          {
          if(OPCODE_INFO[opcode].size != -1)
             {
             DEBUGPRINT( "** " << OPCODE_INFO[opcode].name << " (size " <<
                         OPCODE_INFO[opcode].size << ")" << std::endl );
             skip_offset = OPCODE_INFO[opcode].size - 2; // opcode already read
             }
          else
             {
             DEBUGPRINT( "BGL Error: Unhandled opcode " << OPCODE_INFO[opcode].name
                         << " (" << hex << opcode << dec << ")" << endl );
             }
          }
       else
          {
          DEBUGPRINT( "BGL Error: Op-code out of range: " << hex << opcode << dec << endl );
          }
       break;
       }
    }

 if (skip_offset > 0)
    {
    cerr << "*** skipping " << skip_offset << " bytes\n";
    reader_->IncPtr(skip_offset);
    }
}

//===========================================================================

void BGLParser::BEOF(Enum16 opcode)
{
 DEBUGPRINT("BGL_EOF (" << hex << opcode << dec << "):\n");
 done_ = true;
}

//===========================================================================

void BGLParser::OBSOLETE(Enum16 opcode)
{
 DEBUGPRINT("BGL_OBSOLETE (" << hex << opcode << dec << "):\n");
}

//===========================================================================

void BGLParser::RESERVED(Enum16 opcode)
{
 DEBUGPRINT("BGL_RESERVED (" << hex << opcode << dec << "):\n");
}

//===========================================================================

void BGLParser::NOOP(Enum16 opcode)
{
 DEBUGPRINT("BGL_NOOP (" << hex << opcode << dec << "):\n");
}

//===========================================================================

void BGLParser::CASE(Enum16 opcode,
                     UInt16 number,
                     SInt16 token,
                     SInt16 fail_jump,
                     SInt16 jumps[])
{
 DEBUGPRINT("BGL_CASE (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  number	 = " << number << endl);
 DEBUGPRINT("  token	 = " << token << endl);
 DEBUGPRINT("  fail_jump	 = " << fail_jump << endl);
// DEBUGPRINT("  jumps[]	 = " << jumps[] << endl);
}

//===========================================================================

void BGLParser::SURFACE(Enum16 opcode)
{
 DEBUGPRINT("BGL_SURFACE (" << hex << opcode << dec << "):\n");
}

//===========================================================================

void BGLParser::SPNT(Enum16 opcode,
                     XYZ16 point)
{
 DEBUGPRINT("BGL_SPNT (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  point	 = " << point.x << ", " << point.y << ", " << point.z << endl);
}

//===========================================================================

void BGLParser::CPNT(Enum16 opcode,
                     XYZ16 point)
{
 DEBUGPRINT("BGL_CPNT (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  point	 = " << point.x << ", " << point.y << ", " << point.z << endl);
}

//===========================================================================

void BGLParser::CLOSURE(Enum16 opcode)
{
 DEBUGPRINT("BGL_CLOSURE (" << hex << opcode << dec << "):\n");
}

//===========================================================================

void BGLParser::JUMP(Enum16 opcode, SInt16 dst)
{
 DEBUGPRINT("BGL_JUMP (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  jump	 = " << dst << endl);

 jump(dst - 4);
}

//===========================================================================

void BGLParser::DEFRES(Enum16 opcode,
                       UInt16 index,
                       XYZ16 vertex)
{
 DEBUGPRINT("BGL_DEFRES (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  index	 = " << index << endl);
// DEBUGPRINT("  vertex	 = " << vertex << endl);
}

//===========================================================================

void BGLParser::STRRES(Enum16 opcode,
                       UInt16 index)
{
 DEBUGPRINT("BGL_STRRES (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  index	 = " << index << endl);
}

//===========================================================================

void BGLParser::CNTRES(Enum16 opcode,
                       UInt16 index)
{
 DEBUGPRINT("BGL_CNTRES (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  index	 = " << index << endl);
}

//===========================================================================

void BGLParser::SCOLOR(Enum16 opcode,
                       UInt16 color)
{
 DEBUGPRINT("BGL_SCOLOR (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  color	 = 0x" << hex << color << dec << endl);
}

//===========================================================================

void BGLParser::ELEVATION_MAP(Enum16 opcode,
                              UInt16 grid_size_x,
                              UInt16 grid_size_y,
                              UInt16 square_size_x,
                              UInt16 square_size_z,
                              SInt16 starting_x,
                              SInt16 starting_z,
                              SInt16 min_altitude,
                              SInt16 max_altitude,
                              const SInt16* elevation_points)
{
 DEBUGPRINT("BGL_ELEVATION_MAP (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  grid_size_x	 = " << grid_size_x << endl);
 DEBUGPRINT("  grid_size_y	 = " << grid_size_y << endl);
 DEBUGPRINT("  square_size_x	 = " << square_size_x << endl);
 DEBUGPRINT("  square_size_z	 = " << square_size_z << endl);
 DEBUGPRINT("  starting_x	 = " << starting_x << endl);
 DEBUGPRINT("  starting_z	 = " << starting_z << endl);
 DEBUGPRINT("  min_altitude	 = " << min_altitude << endl);
 DEBUGPRINT("  max_altitude	 = " << max_altitude << endl);
// DEBUGPRINT("  SInt16*	 = " << SInt16* << endl);
}

//===========================================================================

void BGLParser::TEXTURE_ENABLE(Enum16 opcode,
                               Bool16 onoff)
{
 DEBUGPRINT("BGL_TEXTURE_ENABLE (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  onoff	 = " << onoff << endl);
}

//===========================================================================

void BGLParser::TEXTURE1(Enum16 opcode,
                         UInt16 index,
                         SInt16 bias_x,
                         SInt16 free,
                         SInt16 bias_z,
                         const STRINGZ* name)
{
 DEBUGPRINT("BGL_TEXTURE (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  index	 = " << index << endl);
 DEBUGPRINT("  bias_x	 = " << bias_x << endl);
 DEBUGPRINT("  free	 = " << free << endl);
 DEBUGPRINT("  bias_z	 = " << bias_z << endl);
 DEBUGPRINT("  name	 = " << name << endl);
}

//===========================================================================

void BGLParser::PALETTE(Enum16 opcode,
                        const STRINGZ* name)
{
 DEBUGPRINT("BGL_PALETTE (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  name	 = " << name << endl);
}

//===========================================================================

void BGLParser::RESLIST(Enum16 opcode,
                        UInt16 start_index,
                        UInt16 count,
                        const XYZ16* vertex)
{
 DEBUGPRINT("BGL_RESLIST (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  start_index	 = " << start_index << endl);
 DEBUGPRINT("  count	 = " << count << endl);
 DEBUGPRINT("  vertex	 = " << vertex->x << ", " << vertex->y << ", " << vertex->z << endl);

// vertex_.clear();
// vertex_.resize(count*3);

}

//===========================================================================

void BGLParser::IFIN_BOX_RAW_PLANE(Enum16 opcode,
                                   SInt16 fail,
                                   XYZ16 center,
                                   XYZ16 size,
                                   PBH16 rotation)
{
 DEBUGPRINT("BGL_IFIN_BOX_RAW_PLANE (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  fail	 = " << fail << endl);
 DEBUGPRINT("  center	 = " << center.x << ", " << center.y << ", " << center.z << endl);
 DEBUGPRINT("  size	 = " << size.x << ", " << size.y << ", " << size.z << endl);
// DEBUGPRINT("  rotation	 = " << rotation << endl);
}

//===========================================================================

void BGLParser::IFIN2(Enum16 opcode,
                      SInt16 fail,
                      Var16 var1,
                      SInt16 low1,
                      SInt16 high1,
                      Var16 var2,
                      SInt16 low2,
                      SInt16 high2)
{
 DEBUGPRINT("BGL_IFIN2 (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  fail	 = " << fail << endl);
 DEBUGPRINT("  var1	 = 0x" << hex << var1 << dec << endl);
 DEBUGPRINT("  low1	 = " << low1 << endl);
 DEBUGPRINT("  high1	 = " << high1 << endl);
 DEBUGPRINT("  var2	 = 0x" << hex << var2 << dec << endl);
 DEBUGPRINT("  low2	 = " << low2 << endl);
 DEBUGPRINT("  high2	 = " << high2 << endl);
}

//===========================================================================

void BGLParser::FACE(Enum16 opcode,
                     UInt16 count,
                     XYZ16 point,
                     XYZ16 normal,
                     const UInt16* vertices)
{
 DEBUGPRINT("BGL_FACE (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  count	 = " << count << endl);
// DEBUGPRINT("  point	 = " << point << endl);
// DEBUGPRINT("  normal	 = " << normal << endl);
// DEBUGPRINT("  UInt16*	 = " << UInt16* << endl);
}

//===========================================================================

void BGLParser::HAZE(Enum16 opcode,
                     UInt16 factor)
{
 DEBUGPRINT("BGL_HAZE (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  factor	 = " << factor << endl);
}

//===========================================================================

void BGLParser::FACET_TMAP(Enum16 opcode,
                           UInt16 count,
                           XYZ16 normal,
                           SInt32 dot_ref,
                           const PXZ16* vertices)
{
 DEBUGPRINT("BGL_FACET_TMAP (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  count	 = " << count << endl);
// DEBUGPRINT("  normal	 = " << normal << endl);
 DEBUGPRINT("  dot_ref	 = " << dot_ref << endl);
// DEBUGPRINT("  PXZ16*	 = " << PXZ16* << endl);
}

//===========================================================================

void BGLParser::GFACET_TMAP(Enum16 opcode,
                           UInt16 count,
                           XYZ16 normal,
                           SInt32 dot_ref,
                           const PXZ16* vertices)
{
 DEBUGPRINT("BGL_GFACET_TMAP (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  count	 = " << count << endl);
// DEBUGPRINT("  normal	 = " << normal << endl);
 DEBUGPRINT("  dot_ref	 = " << dot_ref << endl);
// DEBUGPRINT("  PXZ16*	 = " << PXZ16* << endl);
}

//===========================================================================

void BGLParser::IFIN3(Enum16 opcode,
                      SInt16 fail,
                      Var16 var1,
                      SInt16 low1,
                      SInt16 high1,
                      Var16 var2,
                      SInt16 low2,
                      SInt16 high2,
                      Var16 var3,
                      SInt16 low3,
                      SInt16 high3)
{
 DEBUGPRINT("BGL_IFIN3 (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  fail	 = " << fail << endl);
 DEBUGPRINT("  var1	 = " << hex << var1 << dec << endl);
 DEBUGPRINT("  low1	 = " << low1 << endl);
 DEBUGPRINT("  high1	 = " << high1 << endl);
 DEBUGPRINT("  var2	 = " << hex << var2 << dec << endl);
 DEBUGPRINT("  low2	 = " << low2 << endl);
 DEBUGPRINT("  high2	 = " << high2 << endl);
 DEBUGPRINT("  var3	 = " << hex << var3 << dec << endl);
 DEBUGPRINT("  low3	 = " << low3 << endl);
 DEBUGPRINT("  high3	 = " << high3 << endl);
}

//===========================================================================

void BGLParser::RETURN(Enum16 opcode)
{
 DEBUGPRINT("BGL_RETURN (" << hex << opcode << dec << "):\n");

 if(opcode_stack_.empty())
    {
    cerr << "**** Warning: RETURN empty opcode stack! ****\n";
    }
 else
    opcode_stack_.pop_front();

 if(stack_.size() == 0)
    {
    cerr << "warning: stack underflow! - quit parsing\n";
    done_ = true;
    }
 else
    {
    long addr = stack_.front();
    stack_.pop_front();
    reader_->SetCurrentPos(addr);
    }
}

//===========================================================================

void BGLParser::CALL(Enum16 opcode,
                     SInt16 call)
{
 DEBUGPRINT("BGL_CALL (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  call	 = " << call << endl);

 opcode_stack_.push_front(BGL_CALL);
 callSub(call - 4);
}

//===========================================================================

void BGLParser::IFIN1(Enum16 opcode,
                      SInt16 fail,
                      Var16 var,
                      SInt16 low,
                      SInt16 high)
{
 DEBUGPRINT("BGL_IFIN1 (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  fail	 = " << fail << endl);
 DEBUGPRINT("  var	 = 0x" << hex << var << dec << endl);
 DEBUGPRINT("  low	 = " << low << endl);
 DEBUGPRINT("  high	 = " << high << endl);

// if(var == 0x7a && high == 31999)
//    jump(fail - 10);

// if(var == 0x7a && high == 32007)
//    jump(fail - 10);
}

//===========================================================================

void BGLParser::SEPARATION_PLANE(Enum16 opcode,
                                 SInt16 alternate_jump,
                                 XYZ16 normal,
                                 SInt32 dot_ref)
{
 DEBUGPRINT("BGL_SEPARATION_PLANE (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  alternate_jump	 = " << alternate_jump << endl);
// DEBUGPRINT("  normal	 = " << normal << endl);
 DEBUGPRINT("  dot_ref	 = " << dot_ref << endl);
}

//===========================================================================

void BGLParser::SETWRD(Enum16 opcode,
                       Var16 var,
                       SInt16 value)
{
 DEBUGPRINT("BGL_SETWRD (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  var	 = 0x" << hex << var << dec << endl);
 DEBUGPRINT("  value	 = " << value << endl);
}

//===========================================================================

void BGLParser::GRESLIST(Enum16 opcode,
                         UInt16 start_index,
                         UInt16 count,
                         const GVERTEX* vertex)
{
 DEBUGPRINT("BGL_GRESLIST (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  start_index	 = " << start_index << endl);
 DEBUGPRINT("  count	 = " << count << endl);
// DEBUGPRINT("  GVERTEX*	 = " << GVERTEX* << endl);
}

//===========================================================================

void BGLParser::GFACET(Enum16 opcode,
                       UInt16 count,
                       XYZ16 normal,
                       SInt32 dot_ref,
                       const UInt16* vertices)
{
 DEBUGPRINT("BGL_GFACET (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  count	 = " << count << endl);
// DEBUGPRINT("  normal	 = " << normal << endl);
 DEBUGPRINT("  dot_ref	 = " << dot_ref << endl);
// DEBUGPRINT("  UInt16*	 = " << UInt16* << endl);
}

//===========================================================================

void BGLParser::ADDOBJ32(Enum16 opcode,
                         SInt32 call)
{
 DEBUGPRINT("BGL_ADDOBJ32 (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  call	 = " << call << endl);

 opcode_stack_.push_front(BGL_ADDOBJ32);
 callSub(call - 6);
}

//===========================================================================

void BGLParser::REJECT(Enum16 opcode,
                       SInt16 fail,
                       XYZ16 center,
                       UInt16 radius)
{
 DEBUGPRINT("BGL_REJECT (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  fail	 = " << fail << endl);
// DEBUGPRINT("  center	 = " << center << endl);
 DEBUGPRINT("  radius	 = " << radius << endl);
}

//===========================================================================

void BGLParser::SCOLOR24(Enum16 opcode,
                         UNICOL color)
{
 DEBUGPRINT("BGL_SCOLOR24 (" << hex << opcode << dec << "):\n");
// DEBUGPRINT("  color	 = " << color << endl);
}

//===========================================================================

void BGLParser::LCOLOR24(Enum16 opcode,
                         UNICOL color)
{
 DEBUGPRINT("BGL_LCOLOR24 (" << hex << opcode << dec << "):\n");
// DEBUGPRINT("  color	 = " << color << endl);
}

//===========================================================================

void BGLParser::SCALE(Enum16 opcode,
                      SInt16 fail,
                      UInt16 range,
                      UInt16 size,
                      Var16 index,
                      UInt32 scale,
                      LLA lla)
{
 DEBUGPRINT("BGL_SCALE (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  fail	 = " << fail << endl);
 DEBUGPRINT("  range	 = " << range << endl);
 DEBUGPRINT("  size	 = " << size << endl);
 DEBUGPRINT("  index	 = " << index << endl);
 DEBUGPRINT("  scale	 = " << scale << endl);
 DEBUGPRINT("  lla	 = " << lla << endl);
}

//===========================================================================

void BGLParser::RESROW(Enum16 opcode,
                       UInt16 start_index,
                       UInt16 count,
                       XYZ16 starting_point,
                       XYZ16 ending_point)
{
 DEBUGPRINT("BGL_RESROW (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  start_index	 = " << start_index << endl);
 DEBUGPRINT("  count	 = " << count << endl);
// DEBUGPRINT("  starting_point	 = " << starting_point << endl);
// DEBUGPRINT("  ending_point	 = " << ending_point << endl);
}

//===========================================================================

void BGLParser::ADDOBJ(Enum16 opcode,
                       SInt16 call)
{
 DEBUGPRINT("BGL_ADDOBJ (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  call	 = " << call << endl);

 opcode_stack_.push_front(BGL_ADDOBJ);
 callSub(call - 4);
}

//===========================================================================

void BGLParser::INSTANCE(Enum16 opcode,
                         SInt16 call,
                         PBH16 rotation)
{
 DEBUGPRINT("BGL_INSTANCE (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  call	 = " << call << endl);
// DEBUGPRINT("  rotation	 = " << rotation << endl);

 opcode_stack_.push_front(BGL_INSTANCE);
 callSub(call - 10);
}

//===========================================================================

void BGLParser::SUPER_SCALE(Enum16 opcode,
                            SInt16 fail,
                            UInt16 range,
                            UInt16 size,
                            UInt16 super_scale)
{
 DEBUGPRINT("BGL_SUPER_SCALE (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  fail	 = " << fail << endl);
 DEBUGPRINT("  range	 = " << range << endl);
 DEBUGPRINT("  size	 = " << size << endl);
 DEBUGPRINT("  super_scale	 = " << super_scale << endl);

 if(super_scale <= 16)
    unit_scale_ = (double)((1 << (16 - super_scale)));
 else
    unit_scale_ = 1.0/(1 << (super_scale - 16));

 unit_scale_ = 1.0/unit_scale_;

 cerr << "unit scale = " << unit_scale_ << endl;
}

//===========================================================================

void BGLParser::PNTROW(Enum16 opcode,
                       XYZ16 starting_point,
                       XYZ16 ending_point,
                       UInt16 count)
{
 DEBUGPRINT("BGL_PNTROW (" << hex << opcode << dec << "):\n");
// DEBUGPRINT("  starting_point	 = " << starting_point << endl);
// DEBUGPRINT("  ending_point	 = " << ending_point << endl);
 DEBUGPRINT("  count	 = " << count << endl);
}

//===========================================================================

void BGLParser::POINT(Enum16 opcode,
                      XYZ16 point)
{
 DEBUGPRINT("BGL_POINT (" << hex << opcode << dec << "):\n");
// DEBUGPRINT("  point	 = " << point << endl);
}

//===========================================================================

void BGLParser::CONCAVE(Enum16 opcode)
{
 DEBUGPRINT("BGL_CONCAVE (" << hex << opcode << dec << "):\n");
}

//===========================================================================

void BGLParser::IFMSK(Enum16 opcode,
                      SInt16 fail,
                      Var16 var,
                      Var16 mask)
{
 DEBUGPRINT("BGL_IFMSK (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  fail	 = " << fail << endl);
 DEBUGPRINT("  var	 = 0x" << hex << var << dec << endl);
 DEBUGPRINT("  mask	 = 0x" << hex << mask << dec << endl);

 if(var == 0x7e)
    jump(fail - 8);

// if(var == 0x90 && mask == 0xf)
//    jump(fail - 8);
}

//===========================================================================

void BGLParser::VPOSITION(Enum16 opcode,
                          SInt16 fail,
                          UInt16 range,
                          UInt16 size,
                          Var16 index,
                          Var16 var)
{
 DEBUGPRINT("BGL_VPOSITION (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  fail	 = " << fail << endl);
 DEBUGPRINT("  range	 = " << range << endl);
 DEBUGPRINT("  size	 = " << size << endl);
 DEBUGPRINT("  index	 = " << index << endl);
 DEBUGPRINT("  var	 = " << var << endl);
}

//===========================================================================

void BGLParser::VINSTANCE(Enum16 opcode,
                          SInt16 call,
                          Var16 var)
{
 DEBUGPRINT("BGL_VINSTANCE (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  call	 = " << call << endl);
 DEBUGPRINT("  var	 = " << hex << var << dec << endl);

 opcode_stack_.push_front(BGL_VINSTANCE);
 callSub(call - 6);
}

//===========================================================================

void BGLParser::POSITION(Enum16 opcode,
                         SInt16 fail,
                         UInt16 range,
                         UInt16 size,
                         Var16 index,
                         LLA lla)
{
 DEBUGPRINT("BGL_POSITION (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  fail	 = " << fail << endl);
 DEBUGPRINT("  range	 = " << range << endl);
 DEBUGPRINT("  size	 = " << size << endl);
 DEBUGPRINT("  index	 = " << index << endl);
 DEBUGPRINT("  lla	 = " << lla << endl);
}

//===========================================================================

void BGLParser::SEED(Enum16 opcode)
{
 DEBUGPRINT("BGL_SEED (" << hex << opcode << dec << "):\n");
}

//===========================================================================

void BGLParser::FACET(Enum16 opcode,
                      UInt16 count,
                      XYZ16 normal,
                      SInt32 dot_ref,
                      const UInt16* vertices)
{
 DEBUGPRINT("BGL_FACET (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  count	 = " << count << endl);
// DEBUGPRINT("  normal	 = " << normal << endl);
 DEBUGPRINT("  dot_ref	 = " << dot_ref << endl);
// DEBUGPRINT("  UInt16*	 = " << UInt16* << endl);
}

//===========================================================================

void BGLParser::SHADOW_CALL(Enum16 opcode,
                            SInt16 call)
{
 DEBUGPRINT("BGL_SHADOW_CALL (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  call	 = " << call << endl);

 opcode_stack_.push_front(BGL_SHADOW_CALL);
 callSub(call - 4);
}

//===========================================================================

void BGLParser::SHADOW_VPOSITION(Enum16 opcode,
                                 SInt16 fail,
                                 UInt16 range,
                                 UInt16 size,
                                 Var16 index,
                                 Var16 vlla)
{
 DEBUGPRINT("BGL_SHADOW_VPOSITION (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  fail	 = " << fail << endl);
 DEBUGPRINT("  range	 = " << range << endl);
 DEBUGPRINT("  size	 = " << size << endl);
 DEBUGPRINT("  index	 = " << index << endl);
 DEBUGPRINT("  vlla	 = " << vlla << endl);
}

//===========================================================================

void BGLParser::SHADOW_VICALL(Enum16 opcode,
                              SInt16 call,
                              Var16 vpbh)
{
 DEBUGPRINT("BGL_SHADOW_VICALL (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  call	 = " << call << endl);
 DEBUGPRINT("  vpbh	 = " << vpbh << endl);

 opcode_stack_.push_front(BGL_SHADOW_VICALL);
 callSub(call - 6);
}

//===========================================================================

void BGLParser::POLYGON_RUNWAY(Enum16 opcode,
                               LLA center,
                               Angl16 heading,
                               UInt16 length,
                               UInt16 width,
                               Flags8 flags,
                               Flags8 identifiers,
                               Flags8 surface_lights,
                               Flags8 specials,
                               Enum8 surface_type,
                               Flags8 threshold_flags,
                               UInt16 base_threshold,
                               UInt16 base_blast_pad,
                               UInt16 recip_threshold,
                               UInt16 recip_blast_pad,
                               Flags8 base_app_flags,
                               Enum8 base_app_system,
                               Enum8 base_app_strobes,
                               Flags8 base_vasi_system,
                               Angl16 base_vasi_angle,
                               SInt16 base_vasi_x,
                               SInt16 base_vasi_z,
                               SInt16 base_vasi_spacing,
                               Flags8 recip_app_flags,
                               Enum8 recip_app_system,
                               Enum8 recip_app_strobes,
                               Flags8 recip_vasi_system,
                               Angl16 recip_vasi_angle,
                               SInt16 recip_vasi_x,
                               SInt16 recip_vasi_z,
                               SInt16 recip_vasi_spacing)
{
 DEBUGPRINT("BGL_POLYGON_RUNWAY (" << hex << opcode << dec << "):\n");
// DEBUGPRINT("  center	 = " << center << endl);
 DEBUGPRINT("  heading	 = " << heading << endl);
 DEBUGPRINT("  length	 = " << length << endl);
 DEBUGPRINT("  width	 = " << width << endl);
 DEBUGPRINT("  flags	 = " << flags << endl);
 DEBUGPRINT("  identifiers	 = " << identifiers << endl);
 DEBUGPRINT("  surface_lights	 = " << surface_lights << endl);
 DEBUGPRINT("  specials	 = " << specials << endl);
 DEBUGPRINT("  surface_type	 = " << surface_type << endl);
 DEBUGPRINT("  threshold_flags	 = " << threshold_flags << endl);
 DEBUGPRINT("  base_threshold	 = " << base_threshold << endl);
 DEBUGPRINT("  base_blast_pad	 = " << base_blast_pad << endl);
 DEBUGPRINT("  recip_threshold	 = " << recip_threshold << endl);
 DEBUGPRINT("  recip_blast_pad	 = " << recip_blast_pad << endl);
 DEBUGPRINT("  base_app_flags	 = " << base_app_flags << endl);
 DEBUGPRINT("  base_app_system	 = " << base_app_system << endl);
 DEBUGPRINT("  base_app_strobes	 = " << base_app_strobes << endl);
 DEBUGPRINT("  base_vasi_system	 = " << base_vasi_system << endl);
 DEBUGPRINT("  base_vasi_angle	 = " << base_vasi_angle << endl);
 DEBUGPRINT("  base_vasi_x	 = " << base_vasi_x << endl);
 DEBUGPRINT("  base_vasi_z	 = " << base_vasi_z << endl);
 DEBUGPRINT("  base_vasi_spacing	 = " << base_vasi_spacing << endl);
 DEBUGPRINT("  recip_app_flags	 = " << recip_app_flags << endl);
 DEBUGPRINT("  recip_app_system	 = " << recip_app_system << endl);
 DEBUGPRINT("  recip_app_strobes	 = " << recip_app_strobes << endl);
 DEBUGPRINT("  recip_vasi_system	 = " << recip_vasi_system << endl);
 DEBUGPRINT("  recip_vasi_angle	 = " << recip_vasi_angle << endl);
 DEBUGPRINT("  recip_vasi_x	 = " << recip_vasi_x << endl);
 DEBUGPRINT("  recip_vasi_z	 = " << recip_vasi_z << endl);
 DEBUGPRINT("  recip_vasi_spacing	 = " << recip_vasi_spacing << endl);
}

//===========================================================================

void BGLParser::TEXTURE2(Enum16 opcode,
                         UInt16 length,
                         UInt16 index,
                         Flags8 characteristics,
                         UInt8 checksum,
                         UNICOL color,
                         const STRINGZ* name)
{
 DEBUGPRINT("BGL_TEXTURE2 (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  length	 = " << length << endl);
 DEBUGPRINT("  index	 = " << index << endl);
 DEBUGPRINT("  characteristics	 = " << characteristics << endl);
 DEBUGPRINT("  checksum	 = " << checksum << endl);
// DEBUGPRINT("  color	 = " << color << endl);
 DEBUGPRINT("  name	 = " << name << endl);
}

//===========================================================================

void BGLParser::TEXTURE_RUNWAY(Enum16 opcode,
                               LLA center,
                               Angl16 heading,
                               UInt16 length,
                               UInt16 width,
                               Flags8 flags,
                               Flags8 identifiers,
                               Flags8 surface_lights,
                               Flags8 specials,
                               Enum8 surface_type,
                               Flags8 threshold_flags,
                               UInt16 base_threshold,
                               UInt16 base_blast_pad,
                               UInt16 recip_threshold,
                               UInt16 recip_blast_pad,
                               Flags8 base_app_flags,
                               Enum8 base_app_system,
                               Enum8 base_app_strobes,
                               Flags8 base_vasi_system,
                               Angl16 base_vasi_angle,
                               SInt16 base_vasi_x,
                               SInt16 base_vasi_z,
                               SInt16 base_vasi_spacing,
                               Flags8 recip_app_flags,
                               Enum8 recip_app_system,
                               Enum8 recip_app_strobes,
                               Flags8 recip_vasi_system,
                               Angl16 recip_vasi_angle,
                               SInt16 recip_vasi_x,
                               SInt16 recip_vasi_z,
                               SInt16 recip_vasi_spacing)
{
 DEBUGPRINT("BGL_TEXTURE_RUNWAY (" << hex << opcode << dec << "):\n");
// DEBUGPRINT("  center	 = " << center << endl);
 DEBUGPRINT("  heading	 = " << heading << endl);
 DEBUGPRINT("  length	 = " << length << endl);
 DEBUGPRINT("  width	 = " << width << endl);
 DEBUGPRINT("  flags	 = " << flags << endl);
 DEBUGPRINT("  identifiers	 = " << identifiers << endl);
 DEBUGPRINT("  surface_lights	 = " << surface_lights << endl);
 DEBUGPRINT("  specials	 = " << specials << endl);
 DEBUGPRINT("  surface_type	 = " << surface_type << endl);
 DEBUGPRINT("  threshold_flags	 = " << threshold_flags << endl);
 DEBUGPRINT("  base_threshold	 = " << base_threshold << endl);
 DEBUGPRINT("  base_blast_pad	 = " << base_blast_pad << endl);
 DEBUGPRINT("  recip_threshold	 = " << recip_threshold << endl);
 DEBUGPRINT("  recip_blast_pad	 = " << recip_blast_pad << endl);
 DEBUGPRINT("  base_app_flags	 = " << base_app_flags << endl);
 DEBUGPRINT("  base_app_system	 = " << base_app_system << endl);
 DEBUGPRINT("  base_app_strobes	 = " << base_app_strobes << endl);
 DEBUGPRINT("  base_vasi_system	 = " << base_vasi_system << endl);
 DEBUGPRINT("  base_vasi_angle	 = " << base_vasi_angle << endl);
 DEBUGPRINT("  base_vasi_x	 = " << base_vasi_x << endl);
 DEBUGPRINT("  base_vasi_z	 = " << base_vasi_z << endl);
 DEBUGPRINT("  base_vasi_spacing	 = " << base_vasi_spacing << endl);
 DEBUGPRINT("  recip_app_flags	 = " << recip_app_flags << endl);
 DEBUGPRINT("  recip_app_system	 = " << recip_app_system << endl);
 DEBUGPRINT("  recip_app_strobes	 = " << recip_app_strobes << endl);
 DEBUGPRINT("  recip_vasi_system	 = " << recip_vasi_system << endl);
 DEBUGPRINT("  recip_vasi_angle	 = " << recip_vasi_angle << endl);
 DEBUGPRINT("  recip_vasi_x	 = " << recip_vasi_x << endl);
 DEBUGPRINT("  recip_vasi_z	 = " << recip_vasi_z << endl);
 DEBUGPRINT("  recip_vasi_spacing	 = " << recip_vasi_spacing << endl);
}

//===========================================================================

void BGLParser::POINT_VICALL(Enum16 opcode,
                             SInt16 call,
                             XYZ16 offset,
                             Angl16 pitch,
                             SInt16 vpitch,
                             Angl16 bank,
                             SInt16 vbank,
                             Angl16 heading,
                             SInt16 vheading)
{
 DEBUGPRINT("BGL_POINT_VICALL (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  call	 = " << call << endl);
 DEBUGPRINT("  offset	 = " << offset.x << ", " << offset.y << ", " << offset.z << endl);
 DEBUGPRINT("  pitch	 = " << pitch << endl);
 DEBUGPRINT("  vpitch	 = " << vpitch << endl);
 DEBUGPRINT("  bank	 = " << bank << endl);
 DEBUGPRINT("  vbank	 = " << vbank << endl);
 DEBUGPRINT("  heading	 = " << heading << endl);
 DEBUGPRINT("  vheading	 = " << vheading << endl);

 opcode_stack_.push_front(BGL_POINT_VICALL);
 callSub(call - 22);
}

//===========================================================================

void BGLParser::Var_SEG(Enum16 opcode,
                        UInt16 dummy)
{
 DEBUGPRINT("BGL_Var_SEG (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  dummy	 = " << dummy << endl);
}

//===========================================================================

void BGLParser::BUILDING(Enum16 opcode,
                         Flags16 info,
                         Flags16 codes,
                         XYZ16 offset,
                         UInt16 stories,
                         UInt16 size_x,
                         UInt16 size_z)
{
 DEBUGPRINT("BGL_BUILDING (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  info	 = " << info << endl);
 DEBUGPRINT("  codes	 = " << codes << endl);
// DEBUGPRINT("  offset	 = " << offset << endl);
 DEBUGPRINT("  stories	 = " << stories << endl);
 DEBUGPRINT("  size_x	 = " << size_x << endl);
 DEBUGPRINT("  size_z	 = " << size_z << endl);
}

//===========================================================================

void BGLParser::VSCALE(Enum16 opcode,
                       SInt16 fail,
                       UInt16 range,
                       UInt16 size,
                       Var16 index,
                       UInt32 scale,
                       SInt16 vlla)
{
 DEBUGPRINT("BGL_VSCALE (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  fail	 = " << fail << endl);
 DEBUGPRINT("  range	 = " << range << endl);
 DEBUGPRINT("  size	 = " << size << endl);
 DEBUGPRINT("  index	 = " << index << endl);
 DEBUGPRINT("  scale	 = " << scale << endl);
 DEBUGPRINT("  vlla	 = " << vlla << endl);
}

//===========================================================================

void BGLParser::MOVE_L2G(Enum16 opcode,
                         UInt16 global,
                         SInt16 local)
{
 DEBUGPRINT("BGL_MOVE_L2G (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  global	 = " << hex << global << dec << endl);
 DEBUGPRINT("  local	 = " << hex << local << dec << endl);
}

//===========================================================================

void BGLParser::MOVE_G2L(Enum16 opcode,
                         SInt16 local,
                         UInt16 global)
{
 DEBUGPRINT("BGL_MOVE_G2L (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  local	 = " << hex << local << dec << endl);
 DEBUGPRINT("  global	 = " << hex << global << dec << endl);
}

//===========================================================================

void BGLParser::MOVEWORD(Enum16 opcode,
                         SInt16 to,
                         SInt16 from)
{
 DEBUGPRINT("BGL_MOVEWORD (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  to	 = " << hex << to << dec << endl);
 DEBUGPRINT("  from	 = " << hex << from << dec << endl);
}

//===========================================================================

void BGLParser::GCOLOR(Enum16 opcode,
                       Var16 color)
{
 DEBUGPRINT("BGL_GCOLOR (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  color	 = " << hex << color << dec << endl);
}

//===========================================================================

void BGLParser::NEW_LCOLOR(Enum16 opcode,
                           Var16 color)
{
 DEBUGPRINT("BGL_NEW_LCOLOR (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  color	 = " << hex << color << dec << endl);
}

//===========================================================================

void BGLParser::NEW_SCOLOR(Enum16 opcode,
                           Var16 color)
{
 DEBUGPRINT("BGL_NEW_SCOLOR (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  color	 = " << hex << color << dec << endl);
}

//===========================================================================

void BGLParser::SURFACE_TYPE(Enum16 opcode,
                             Enum8 surface_type,
                             Enum8 surface_condition,
                             UInt16 size_x,
                             UInt16 size_z,
                             UInt16 altitude)
{
 DEBUGPRINT("BGL_SURFACE_TYPE (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  surface_type	 = " << surface_type << endl);
 DEBUGPRINT("  surface_condition	 = " << surface_condition << endl);
 DEBUGPRINT("  size_x	 = " << size_x << endl);
 DEBUGPRINT("  size_z	 = " << size_z << endl);
 DEBUGPRINT("  altitude	 = " << altitude << endl);
}

//===========================================================================

void BGLParser::SET_WEATHER(Enum16 opcode,
                            UInt16 length)
{
 DEBUGPRINT("BGL_SET_WEATHER (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  length	 = " << length << endl);
}

//===========================================================================

void BGLParser::WEATHER(Enum16 opcode,
                        Enum8 fixed,
                        Enum8 type,
                        Angl16 heading,
                        UInt16 scalar,
                        UInt16 extra)
{
 DEBUGPRINT("BGL_WEATHER (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  fixed	 = " << fixed << endl);
 DEBUGPRINT("  type	 = " << type << endl);
 DEBUGPRINT("  heading	 = " << heading << endl);
 DEBUGPRINT("  scalar	 = " << scalar << endl);
 DEBUGPRINT("  extra	 = " << extra << endl);
}

//===========================================================================

void BGLParser::TEXTURE_BOUNDS(Enum16 opcode,
                               UInt32 lower_x,
                               UInt32 lower_z,
                               UInt32 upper_x,
                               UInt32 upper_z)
{
 DEBUGPRINT("BGL_TEXTURE_BOUNDS (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  lower_x	 = " << lower_x << endl);
 DEBUGPRINT("  lower_z	 = " << lower_z << endl);
 DEBUGPRINT("  upper_x	 = " << upper_x << endl);
 DEBUGPRINT("  upper_z	 = " << upper_z << endl);
}

//===========================================================================

void BGLParser::TEXTURE_REPEAT(Enum16 opcode,
                               SInt16 bias_x,
                               SInt16 free,
                               SInt16 bias_z)
{
 DEBUGPRINT("BGL_TEXTURE_REPEAT (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  bias_x	 = " << bias_x << endl);
 DEBUGPRINT("  free	 = " << free << endl);
 DEBUGPRINT("  bias_z	 = " << bias_z << endl);
}

//===========================================================================

void BGLParser::IFSIZEV(Enum16 opcode,
                        SInt16 smaller,
                        UInt16 real_size,
                        UInt16 pixels_ref)
{
 DEBUGPRINT("BGL_IFSIZEV (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  smaller	 = " << smaller << endl);
 DEBUGPRINT("  real_size	 = " << real_size << endl);
 DEBUGPRINT("  pixels_ref	 = " << pixels_ref << endl);
// callSub(smaller - 8);
}

//===========================================================================

void BGLParser::FACE_TMAP(Enum16 opcode,
                          UInt16 count,
                          XYZ16 point,
                          XYZ16 normal,
                          const PXZ16* vertices)
{
 DEBUGPRINT("BGL_FACE_TMAP (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  count	 = " << count << endl);
// DEBUGPRINT("  point	 = " << point << endl);
// DEBUGPRINT("  normal	 = " << normal << endl);
// DEBUGPRINT("  PXZ16*	 = " << PXZ16* << endl);
}

//===========================================================================

void BGLParser::IFVIS(Enum16 opcode,
                      SInt16 off_screen,
                      UInt16 count,
                      const UInt16* points)
{
 DEBUGPRINT("BGL_IFVIS (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  off_screen	 = " << off_screen << endl);
 DEBUGPRINT("  count	 = " << count << endl);
// DEBUGPRINT("  UInt16*	 = " << UInt16* << endl);
}

//===========================================================================

void BGLParser::LIBRARY_CALL(Enum16 opcode,
                             UInt16 index,
                             GUid128 library_id)
{
 DEBUGPRINT("BGL_LIBRARY_CALL (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  index	 = " << index << endl);
// DEBUGPRINT("  library_id	 = " << library_id << endl);
}

//===========================================================================

void BGLParser::LIST(Enum16 opcode,
                     SInt16 total_size,
                     UInt16 count,
                     const UInt16* indexes)
{
 DEBUGPRINT("BGL_LIST (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  total_size	 = " << total_size << endl);
 DEBUGPRINT("  count	 = " << count << endl);
// DEBUGPRINT("  UInt16*	 = " << UInt16* << endl);
}

//===========================================================================

void BGLParser::VSCOLOR(Enum16 opcode,
                        Var16 vcolor)
{
 DEBUGPRINT("BGL_VSCOLOR (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  vcolor	 = " << vcolor << endl);
}

//===========================================================================

void BGLParser::VGCOLOR(Enum16 opcode,
                        Var16 vcolor)
{
 DEBUGPRINT("BGL_VGCOLOR (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  vcolor	 = " << vcolor << endl);
}

//===========================================================================

void BGLParser::VLCOLOR(Enum16 opcode,
                        Var16 vcolor)
{
 DEBUGPRINT("BGL_VLCOLOR (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  vcolor	 = " << vcolor << endl);
}

//===========================================================================

void BGLParser::ROAD_START(Enum16 opcode,
                           UInt16 width,
                           XYZ16 point)
{
 DEBUGPRINT("BGL_ROAD_START (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  width	 = " << width << endl);
// DEBUGPRINT("  point	 = " << point << endl);
}

//===========================================================================

void BGLParser::ROAD_CONT(Enum16 opcode,
                          XYZ16 point)
{
 DEBUGPRINT("BGL_ROAD_CONT (" << hex << opcode << dec << "):\n");
// DEBUGPRINT("  point	 = " << point << endl);
}

//===========================================================================

void BGLParser::RIVER_START(Enum16 opcode,
                            UInt16 width,
                            XYZ16 point)
{
 DEBUGPRINT("BGL_RIVER_START (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  width	 = " << width << endl);
// DEBUGPRINT("  point	 = " << point << endl);
}

//===========================================================================

void BGLParser::RIVER_CONT(Enum16 opcode,
                           XYZ16 point)
{
 DEBUGPRINT("BGL_RIVER_CONT (" << hex << opcode << dec << "):\n");
// DEBUGPRINT("  point	 = " << point << endl);
}

//===========================================================================

void BGLParser::IFSIZEH(Enum16 opcode,
                        SInt16 smaller,
                        UInt16 real_size,
                        UInt16 pixels_ref)
{
 DEBUGPRINT("BGL_IFSIZEH (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  smaller	 = " << smaller << endl);
 DEBUGPRINT("  real_size	 = " << real_size << endl);
 DEBUGPRINT("  pixels_ref	 = " << pixels_ref << endl);
}

//===========================================================================

void BGLParser::TAXIWAY_START(Enum16 opcode,
                              UInt16 width,
                              XYZ16 point)
{
 DEBUGPRINT("BGL_TAXIWAY_START (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  width	 = " << width << endl);
// DEBUGPRINT("  point	 = " << point << endl);
}

//===========================================================================

void BGLParser::TAXIWAY_CONT(Enum16 opcode,
                             XYZ16 point)
{
 DEBUGPRINT("BGL_TAXIWAY_CONT (" << hex << opcode << dec << "):\n");
// DEBUGPRINT("  point	 = " << point << endl);
}

//===========================================================================

void BGLParser::AREA_SENSE(Enum16 opcode,
                           SInt16 outside,
                           UInt16 count,
                           const XZ16* point)
{
 DEBUGPRINT("BGL_AREA_SENSE (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  outside	 = " << outside << endl);
 DEBUGPRINT("  count	 = " << count << endl);
// DEBUGPRINT("  XZ16*	 = " << XZ16* << endl);
}

//===========================================================================

void BGLParser::ALTITUDE_SET(Enum16 opcode,
                             SInt16 altitude)
{
 DEBUGPRINT("BGL_ALTITUDE_SET (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  altitude	 = " << altitude << endl);
}

//===========================================================================

void BGLParser::IFINBOXP(Enum16 opcode,
                         SInt16 outside,
                         SInt16 low_x,
                         SInt16 high_x,
                         SInt16 low_y,
                         SInt16 high_y,
                         SInt16 low_z,
                         SInt16 high_z)
{
 DEBUGPRINT("BGL_IFINBOXP (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  outside	 = " << outside << endl);
 DEBUGPRINT("  low_x	 = " << low_x << endl);
 DEBUGPRINT("  high_x	 = " << high_x << endl);
 DEBUGPRINT("  low_y	 = " << low_y << endl);
 DEBUGPRINT("  high_y	 = " << high_y << endl);
 DEBUGPRINT("  low_z	 = " << low_z << endl);
 DEBUGPRINT("  high_z	 = " << high_z << endl);
}

//===========================================================================

void BGLParser::ADDCAT(Enum16 opcode,
                       SInt16 call,
                       Enum16 category)
{
 DEBUGPRINT("BGL_ADDCAT (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  call	 = " << call << endl);
 DEBUGPRINT("  category	 = " << category << endl);

 opcode_stack_.push_front(BGL_ADDCAT);
 callSub(call - 6);
}

//===========================================================================

void BGLParser::ADDMNT(Enum16 opcode,
                       SInt16 call)
{
 DEBUGPRINT("BGL_ADDMNT (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  call	 = " << call << endl);

 opcode_stack_.push_front(BGL_ADDMNT);
 callSub(call - 4);
}

//===========================================================================

void BGLParser::BGL(Enum16 opcode)
{
 DEBUGPRINT("BGL_BGL (" << hex << opcode << dec << "):\n");
}

//===========================================================================

void BGLParser::SCALE_AGL(Enum16 opcode,
                          SInt16 fail,
                          UInt16 range,
                          UInt16 size,
                          Var16 index,
                          UInt32 scale,
                          LLA lla)
{
 DEBUGPRINT("BGL_SCALE_AGL (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  fail	 = " << fail << endl);
 DEBUGPRINT("  range	 = " << range << endl);
 DEBUGPRINT("  size	 = " << size << endl);
 DEBUGPRINT("  index	 = " << index << endl);
 DEBUGPRINT("  scale	 = " << scale << endl);
 DEBUGPRINT("  lla	 = " << lla << endl);

 unit_scale_ = (double)0xffff/scale;
}

//===========================================================================

void BGLParser::ROAD_CONTW(Enum16 opcode,
                           UInt16 width,
                           XYZ16 point)
{
 DEBUGPRINT("BGL_ROAD_CONTW (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  width	 = " << width << endl);
// DEBUGPRINT("  point	 = " << point << endl);
}

//===========================================================================

void BGLParser::RIVER_CONTW(Enum16 opcode,
                            UInt16 width,
                            XYZ16 point)
{
 DEBUGPRINT("BGL_RIVER_CONTW (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  width	 = " << width << endl);
// DEBUGPRINT("  point	 = " << point << endl);
}

//===========================================================================

void BGLParser::SELECT(Enum16 opcode,
                       SInt16 vindex,
                       UInt16 shift_mask,
                       SInt32 list)
{
 DEBUGPRINT("BGL_SELECT (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  vindex	 = " << vindex << endl);
 DEBUGPRINT("  shift_mask	 = " << shift_mask << endl);
 DEBUGPRINT("  list	 = " << list << endl);
}

//===========================================================================

void BGLParser::PERSPECTIVE(Enum16 opcode)
{
 DEBUGPRINT("BGL_PERSPECTIVE (" << hex << opcode << dec << "):\n");
}

//===========================================================================

void BGLParser::SETWRD_GLOBAL(Enum16 opcode,
                              Enum16 gindex,
                              SInt16 value)
{
 DEBUGPRINT("BGL_SETWRD_GLOBAL (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  gindex	 = 0x" << hex << gindex << dec << endl);
 DEBUGPRINT("  value	 = " << value << endl);
}

//===========================================================================

void BGLParser::RESPNT(Enum16 opcode,
                       Enum16 pindex)
{
 DEBUGPRINT("BGL_RESPNT (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  pindex	 = " << pindex << endl);
}

//===========================================================================

void BGLParser::RESCALE(Enum16 opcode,
                        SInt16 fail,
                        UInt16 range,
                        UInt16 size,
                        UInt32 scale)
{
 DEBUGPRINT("BGL_RESCALE (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  fail	 = " << fail << endl);
 DEBUGPRINT("  range	 = " << range << endl);
 DEBUGPRINT("  size	 = " << size << endl);
 DEBUGPRINT("  scale	 = " << scale << endl);
}

//===========================================================================

void BGLParser::FIXED_COLORS(Enum16 opcode,
                             UInt16 count)
{
 DEBUGPRINT("BGL_FIXED_COLORS (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  count	 = " << count << endl);
}

//===========================================================================

void BGLParser::JUMP32(Enum16 opcode,
                       SInt32 dst)
{
 DEBUGPRINT("BGL_JUMP32 (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  jump	 = " << dst << endl);

 jump(dst - 6);
}

//===========================================================================

void BGLParser::Var_BASE32(Enum16 opcode,
                           Var32 address)
{
 DEBUGPRINT("BGL_Var_BASE32 (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  address	 = " << address << endl);
 if(abs(address) > 1)
    var_base32_ = reader_->GetCurrentPos() + address - 6;
// else
//    var_base32_ = address;
}

//===========================================================================

void BGLParser::CALL32(Enum16 opcode,
                       SInt32 call)
{
 DEBUGPRINT("BGL_CALL32 (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  call	 = " << call << endl);

 opcode_stack_.push_front(BGL_CALL32);
 callSub(call - 6);
}

//===========================================================================

void BGLParser::ADDCAT32(Enum16 opcode,
                         SInt32 call,
                         Enum16 category)
{
 DEBUGPRINT("BGL_ADDCAT32 (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  call	 = " << call << endl);
 DEBUGPRINT("  category	 = " << category << endl);

 opcode_stack_.push_front(BGL_ADDCAT32);
 callSub(call - 8);
}

//===========================================================================

void BGLParser::VFILE_MARKER(Enum16 opcode,
                             SInt16 offset)
{
 DEBUGPRINT("BGL_VFILE_MARKER (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  offset	 = " << offset << endl);
}

//===========================================================================

void BGLParser::ALPHA(Enum16 opcode,
                      UInt32 value)
{
 DEBUGPRINT("BGL_ALPHA (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  value	 = " << value << endl);
}

//===========================================================================

void BGLParser::BTEXT(Enum16 opcode,
                     XYZ16 start_point,
                     Var16 vtext,
                     Flags16 flags)
{
 DEBUGPRINT("BGL_TEXT (" << hex << opcode << dec << "):\n");
// DEBUGPRINT("  start_point	 = " << start_point << endl);
 DEBUGPRINT("  vtext	 = " << vtext << endl);
 DEBUGPRINT("  flags	 = " << flags << endl);
}

//===========================================================================

void BGLParser::CRASH(Enum16 opcode,
                      UInt16 length,
                      UInt16 ground_radius,
                      SInt16 scale,
                      SInt16 instance,
                      Bool8 processed,
                      Enum8 density)
{
 DEBUGPRINT("BGL_CRASH (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  length	 = " << length << endl);
 DEBUGPRINT("  ground_radius	 = " << ground_radius << endl);
 DEBUGPRINT("  scale	 = " << scale << endl);
 DEBUGPRINT("  instance	 = " << instance << endl);
 DEBUGPRINT("  processed	 = " << processed << endl);
 DEBUGPRINT("  density	 = " << density << endl);
}

//===========================================================================

void BGLParser::CRASH_INDIRECT(Enum16 opcode,
                               SInt16 call,
                               SInt16 scale,
                               SInt16 instance,
                               Bool8 processed,
                               Enum8 density)
{
 DEBUGPRINT("BGL_CRASH_INDIRECT (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  call	 = " << call << endl);
 DEBUGPRINT("  scale	 = " << scale << endl);
 DEBUGPRINT("  instance	 = " << instance << endl);
 DEBUGPRINT("  processed	 = " << processed << endl);
 DEBUGPRINT("  density	 = " << density << endl);

 opcode_stack_.push_front(BGL_CRASH_INDIRECT);
 callSub(call - 10);
}

//===========================================================================

void BGLParser::CRASH_START(Enum16 opcode,
                            UInt16 length,
                            UInt16 ground_radius)
{
 DEBUGPRINT("BGL_CRASH_START (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  length	 = " << length << endl);
 DEBUGPRINT("  ground_radius	 = " << ground_radius << endl);

 reader_->IncPtr(length - 6);
}

//===========================================================================

void BGLParser::CRASH_SPHERE(Enum16 opcode,
                             SInt16 outside,
                             UInt16 radius)
{
 DEBUGPRINT("BGL_CRASH_SPHERE (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  outside	 = " << outside << endl);
 DEBUGPRINT("  radius	 = " << radius << endl);
}

//===========================================================================

void BGLParser::CRASH_BOX(Enum16 opcode,
                          SInt16 outside,
                          XYZ16 center_bias,
                          XYZ16 rectangle,
                          PBH16 pbh)
{
 DEBUGPRINT("BGL_CRASH_BOX (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  outside	 = " << outside << endl);
// DEBUGPRINT("  center_bias	 = " << center_bias << endl);
// DEBUGPRINT("  rectangle	 = " << rectangle << endl);
// DEBUGPRINT("  pbh	 = " << pbh << endl);
}

//===========================================================================

void BGLParser::SET_CRASH(Enum16 opcode,
                          Enum16 type)
{
 DEBUGPRINT("BGL_SET_CRASH (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  type	 = " << type << endl);
}

//===========================================================================

void BGLParser::INTERPOLATE(Enum16 opcode,
                            SInt32 vinput_base,
                            SInt16 vinput,
                            SInt32 voutput_base,
                            SInt16 voutput,
                            SInt32 vtable_base,
                            SInt16 vinput2)
{
 DEBUGPRINT("BGL_INTERPOLATE (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  vinput_base	 = " << vinput_base << endl);
 DEBUGPRINT("  vinput	 = " << vinput << endl);
 DEBUGPRINT("  voutput_base	 = " << voutput_base << endl);
 DEBUGPRINT("  voutput	 = " << voutput << endl);
 DEBUGPRINT("  vtable_base	 = " << vtable_base << endl);
 DEBUGPRINT("  vinput	 = " << vinput << endl);
}

//===========================================================================

void BGLParser::OVERRIDE(Enum16 opcode,
                         SInt32 vbase)
{
 DEBUGPRINT("BGL_OVERRIDE (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  vbase	 = " << vbase << endl);
}

//===========================================================================

void BGLParser::BUILD_RECT_FLAT_ROOF(Enum16 opcode,
                                     UInt16 total_length,
                                     Enum16 category,
                                     const BUILD_RECT_FLAT_ROOF_S& build)
{
 DEBUGPRINT("BGL_BUILD_RECT_FLAT_ROOF (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  total_length	 = " << total_length << endl);
 DEBUGPRINT("  category	 = " << category << endl);
// DEBUGPRINT("  BUILD_RECT_FLAT_ROOF&	 = " << BUILD_RECT_FLAT_ROOF& << endl);
}

//===========================================================================

void BGLParser::BUILD_RECT_RIDGE_ROOF(Enum16 opcode,
                                      UInt16 total_length,
                                      Enum16 category,
                                      const BUILD_RECT_RIDGE_ROOF_S& build)
{
 DEBUGPRINT("BGL_BUILD_RECT_RIDGE_ROOF (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  total_length	 = " << total_length << endl);
 DEBUGPRINT("  category	 = " << category << endl);
// DEBUGPRINT("  BUILD_RECT_RIDGE_ROOF&	 = " << BUILD_RECT_RIDGE_ROOF& << endl);
}

//===========================================================================

void BGLParser::BUILD_RECT_PEAK_ROOF(Enum16 opcode,
                                     UInt16 total_length,
                                     Enum16 category,
                                     const BUILD_RECT_PEAK_ROOF_S& build)
{
 DEBUGPRINT("BGL_BUILD_RECT_PEAK_ROOF (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  total_length	 = " << total_length << endl);
 DEBUGPRINT("  category	 = " << category << endl);
// DEBUGPRINT("  BUILD_RECT_PEAK_ROOF&	 = " << BUILD_RECT_PEAK_ROOF& << endl);
}

//===========================================================================

void BGLParser::BUILD_RECT_SLANT_ROOF(Enum16 opcode,
                                      UInt16 total_length,
                                      Enum16 category,
                                      const BUILD_RECT_SLANT_ROOF_S& build)
{
 DEBUGPRINT("BGL_BUILD_RECT_SLANT_ROOF (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  total_length	 = " << total_length << endl);
 DEBUGPRINT("  category	 = " << category << endl);
// DEBUGPRINT("  BUILD_RECT_SLANT_ROOF&	 = " << BUILD_RECT_SLANT_ROOF& << endl);
}

//===========================================================================

void BGLParser::BUILD_PYRAMID(Enum16 opcode,
                              UInt16 total_length,
                              Enum16 category,
                              const BUILD_PYRAMID_S& build)
{
 DEBUGPRINT("BGL_BUILD_PYRAMID (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  total_length	 = " << total_length << endl);
 DEBUGPRINT("  category	 = " << category << endl);
// DEBUGPRINT("  BUILD_PYRAMID&	 = " << BUILD_PYRAMID& << endl);
}

//===========================================================================

void BGLParser::BUILD_MULTI_SIDED(Enum16 opcode,
                                  UInt16 total_length,
                                  Enum16 category,
                                  const BUILD_MULTI_SIDED_S& build)
{
 DEBUGPRINT("BGL_BUILD_MULTI_SIDED (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  total_length	 = " << total_length << endl);
 DEBUGPRINT("  category	 = " << category << endl);
// DEBUGPRINT("  BUILD_MULTI_SIDED&	 = " << BUILD_MULTI_SIDED& << endl);
}

//===========================================================================

void BGLParser::VALPHA(Enum16 opcode,
                       SInt16 variable)
{
 DEBUGPRINT("BGL_VALPHA (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  variable	 = " << variable << endl);
}

//===========================================================================

void BGLParser::SPRITE_VICALL(Enum16 opcode,
                              SInt16 call,
                              XYZ16 offset,
                              PBH16 pbh,
                              SInt16 vpitch,
                              SInt16 vbank,
                              SInt16 vheading)
{
 DEBUGPRINT("BGL_SPRITE_VICALL (" << hex << opcode << dec << "):\n");
// DEBUGPRINT("  offset	 = " << offset << endl);
// DEBUGPRINT("  pbh	 = " << pbh << endl);
 DEBUGPRINT("  vpitch	 = " << vpitch << endl);
 DEBUGPRINT("  vbank	 = " << vbank << endl);
 DEBUGPRINT("  vheading	 = " << vheading << endl);

 opcode_stack_.push_front(BGL_SPRITE_VICALL);
 callSub(call - 22);
}

//===========================================================================

void BGLParser::TEXTURE_ROAD_START(Enum16 opcode,
                                   Enum16 style,
                                   UInt16 width,
                                   XYZ16 point)
{
 DEBUGPRINT("BGL_TEXTURE_ROAD_START (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  style	 = " << style << endl);
 DEBUGPRINT("  width	 = " << width << endl);
// DEBUGPRINT("  point	 = " << point << endl);
}

//===========================================================================

void BGLParser::IFIN_INSTANCED_BOX_PLANE(Enum16 opcode,
                                         SInt16 fail,
                                         XYZ16 center,
                                         XYZ16 size,
                                         PBH16 rotation)
{
 DEBUGPRINT("BGL_IFIN_INSTANCED_BOX_PLANE (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  fail	 = " << fail << endl);
// DEBUGPRINT("  center	 = " << center << endl);
// DEBUGPRINT("  size	 = " << size << endl);
// DEBUGPRINT("  rotation	 = " << rotation << endl);
}

//===========================================================================

void BGLParser::NEW_RUNWAY(Enum16 opcode,
                           UInt16 total_length)
{
 DEBUGPRINT("BGL_NEW_RUNWAY (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  total_length	 = " << total_length << endl);
}

//===========================================================================

void BGLParser::RWY_RUNWAY_BASE(Enum8 sub_opcode,
                                LLA lla,
                                Angl16 heading,
                                UInt16 length,
                                UInt16 width,
                                Flags16 markings,
                                Enum8 surface_type,
                                Flags8 surface_lights,
                                Flags8 identifiers)
{
 DEBUGPRINT("BGL_RWY_RUNWAY_BASE (" << hex << sub_opcode << dec << "):\n");
 DEBUGPRINT("  lla	 = " << lla << endl);
 DEBUGPRINT("  heading	 = " << heading << endl);
 DEBUGPRINT("  length	 = " << length << endl);
 DEBUGPRINT("  width	 = " << width << endl);
 DEBUGPRINT("  markings	 = " << markings << endl);
 DEBUGPRINT("  surface_type	 = " << surface_type << endl);
 DEBUGPRINT("  surface_lights	 = " << surface_lights << endl);
 DEBUGPRINT("  identifiers	 = " << identifiers << endl);
}

//===========================================================================

void BGLParser::RWY_BASE_THRESHOLD(Enum8 sub_opcode,
                                   UInt8 spare,
                                   UInt16 length)
{
 DEBUGPRINT("BGL_RWY_BASE_THRESHOLD (" << hex << sub_opcode << dec << "):\n");
 DEBUGPRINT("  spare	 = " << spare << endl);
 DEBUGPRINT("  length	 = " << length << endl);
}

//===========================================================================

void BGLParser::RWY_RECIP_THRESHOLD(Enum8 sub_opcode,
                                    UInt8 spare,
                                    UInt16 length)
{
 DEBUGPRINT("BGL_RWY_RECIP_THRESHOLD (" << hex << sub_opcode << dec << "):\n");
 DEBUGPRINT("  spare	 = " << spare << endl);
 DEBUGPRINT("  length	 = " << length << endl);
}

//===========================================================================

void BGLParser::RWY_BASE_BLAST_PAD(Enum8 sub_opcode,
                                   UInt8 spare,
                                   UInt16 length)
{
 DEBUGPRINT("BGL_RWY_BASE_BLAST_PAD (" << hex << sub_opcode << dec << "):\n");
 DEBUGPRINT("  spare	 = " << spare << endl);
 DEBUGPRINT("  length	 = " << length << endl);
}

//===========================================================================

void BGLParser::RWY_RECIP_BLAST_PAD(Enum8 sub_opcode,
                                    UInt8 spare,
                                    UInt16 length)
{
 DEBUGPRINT("BGL_RWY_RECIP_BLAST_PAD (" << hex << sub_opcode << dec << "):\n");
 DEBUGPRINT("  spare	 = " << spare << endl);
 DEBUGPRINT("  length	 = " << length << endl);
}

//===========================================================================

void BGLParser::RWY_BASE_APPROACH_LIGHTS(Enum8 sub_opcode,
                                         UInt8 spare,
                                         Flags8 flags,
                                         Enum8 system,
                                         Enum8 strobes,
                                         Flags8 vasi_system,
                                         Angl16 vasi_angle,
                                         SInt16 vasi_x,
                                         SInt16 vasi_z,
                                         SInt16 vasi_spacing)
{
 DEBUGPRINT("BGL_RWY_BASE_APPROACH_LIGHTS (" << hex << sub_opcode << dec << "):\n");
 DEBUGPRINT("  spare	 = " << spare << endl);
 DEBUGPRINT("  flags	 = " << flags << endl);
 DEBUGPRINT("  system	 = " << system << endl);
 DEBUGPRINT("  strobes	 = " << strobes << endl);
 DEBUGPRINT("  vasi_system	 = " << vasi_system << endl);
 DEBUGPRINT("  vasi_angle	 = " << vasi_angle << endl);
 DEBUGPRINT("  vasi_x	 = " << vasi_x << endl);
 DEBUGPRINT("  vasi_z	 = " << vasi_z << endl);
 DEBUGPRINT("  vasi_spacing	 = " << vasi_spacing << endl);
}

//===========================================================================

void BGLParser::RWY_RECIP_APPROACH_LIGHTS(Enum8 sub_opcode,
                                          UInt8 spare,
                                          Flags8 flags,
                                          Enum8 system,
                                          Enum8 strobes,
                                          Flags8 vasi_system,
                                          Angl16 vasi_angle,
                                          SInt16 vasi_x,
                                          SInt16 vasi_z,
                                          SInt16 vasi_spacing)
{
 DEBUGPRINT("BGL_RWY_RECIP_APPROACH_LIGHTS (" << hex << sub_opcode << dec << "):\n");
 DEBUGPRINT("  spare	 = " << spare << endl);
 DEBUGPRINT("  flags	 = " << flags << endl);
 DEBUGPRINT("  system	 = " << system << endl);
 DEBUGPRINT("  strobes	 = " << strobes << endl);
 DEBUGPRINT("  vasi_system	 = " << vasi_system << endl);
 DEBUGPRINT("  vasi_angle	 = " << vasi_angle << endl);
 DEBUGPRINT("  vasi_x	 = " << vasi_x << endl);
 DEBUGPRINT("  vasi_z	 = " << vasi_z << endl);
 DEBUGPRINT("  vasi_spacing	 = " << vasi_spacing << endl);
}

//===========================================================================

void BGLParser::RWY_BASE_OVERRUN(Enum8 sub_opcode,
                                 Enum8 surface_type,
                                 UInt16 length)
{
 DEBUGPRINT("BGL_RWY_BASE_OVERRUN (" << hex << sub_opcode << dec << "):\n");
 DEBUGPRINT("  surface_type	 = " << surface_type << endl);
 DEBUGPRINT("  length	 = " << length << endl);
}

//===========================================================================

void BGLParser::RWY_RECIP_OVERRUN(Enum8 sub_opcode,
                                  Enum8 surface_type,
                                  UInt16 length)
{
 DEBUGPRINT("BGL_RWY_RECIP_OVERRUN (" << hex << sub_opcode << dec << "):\n");
 DEBUGPRINT("  surface_type	 = " << surface_type << endl);
 DEBUGPRINT("  length	 = " << length << endl);
}

//===========================================================================

void BGLParser::RWY_BASE_DISTANCE_LEFT(Enum8 sub_opcode,
                                       UInt8 info,
                                       UInt16 x_offset)
{
 DEBUGPRINT("BGL_RWY_BASE_DISTANCE_LEFT (" << hex << sub_opcode << dec << "):\n");
 DEBUGPRINT("  info	 = " << info << endl);
 DEBUGPRINT("  x_offset	 = " << x_offset << endl);
}

//===========================================================================

void BGLParser::RWY_RECIP_DISTANCE_LEFT(Enum8 sub_opcode,
                                        UInt8 info,
                                        UInt16 x_offset)
{
 DEBUGPRINT("BGL_RWY_RECIP_DISTANCE_LEFT (" << hex << sub_opcode << dec << "):\n");
 DEBUGPRINT("  info	 = " << info << endl);
 DEBUGPRINT("  x_offset	 = " << x_offset << endl);
}

//===========================================================================

void BGLParser::ZBIAS(Enum16 opcode,
                      UInt16 zbias)
{
 DEBUGPRINT("BGL_ZBIAS (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  zbias	 = " << zbias << endl);
}

//===========================================================================

void BGLParser::ANIMATE(Enum16 opcode,
                        SInt32 vinput_base,
                        SInt32 vinput,
                        SInt32 vtable_base,
                        SInt32 vinput2,
                        Float32 x, Float32 y, Float32 z)
{
 DEBUGPRINT("BGL_ANIMATE (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  vinput_base	 = " << vinput_base << endl);
 DEBUGPRINT("  vinput	 = " << vinput << endl);
 DEBUGPRINT("  vtable_base	 = " << vtable_base << endl);
 DEBUGPRINT("  vinput	 = " << vinput << endl);
}

//===========================================================================

void BGLParser::TRANSFORM_END(Enum16 opcode)
{
 DEBUGPRINT("BGL_TRANSFORM_END (" << hex << opcode << dec << "):\n");
}

//===========================================================================

void BGLParser::TRANSFORM_MATRIX(Enum16 opcode,
                                 XYZF32 values,
                                 Float32 q00,
                                 Float32 q01,
                                 Float32 q02,
                                 Float32 q10,
                                 Float32 q11,
                                 Float32 q12,
                                 Float32 q20,
                                 Float32 q21,
                                 Float32 q22)
{
 DEBUGPRINT("BGL_TRANSFORM_MATRIX (" << hex << opcode << dec << "):\n");
// DEBUGPRINT("  values	 = " << values << endl);
 DEBUGPRINT("  q00	 = " << q00 << endl);
 DEBUGPRINT("  q01	 = " << q01 << endl);
 DEBUGPRINT("  q02	 = " << q02 << endl);
 DEBUGPRINT("  q10	 = " << q10 << endl);
 DEBUGPRINT("  q11	 = " << q11 << endl);
 DEBUGPRINT("  q12	 = " << q12 << endl);
 DEBUGPRINT("  q20	 = " << q20 << endl);
 DEBUGPRINT("  q21	 = " << q21 << endl);
 DEBUGPRINT("  q22	 = " << q22 << endl);
}

//===========================================================================

void BGLParser::LIGHT(Enum16 opcode,
                      Enum16 light_type,
                      XYZF32 location,
                      UInt32 intensity,
                      Float32 reserved,
                      Float32 reserved2,
                      UNICOL color,
                      XYZF32 reserved3)
{
 DEBUGPRINT("BGL_LIGHT (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  light_type	 = " << light_type << endl);
// DEBUGPRINT("  location	 = " << location << endl);
 DEBUGPRINT("  intensity	 = " << intensity << endl);
 DEBUGPRINT("  reserved	 = " << reserved << endl);
 DEBUGPRINT("  reserved	 = " << reserved << endl);
// DEBUGPRINT("  color	 = " << color << endl);
 DEBUGPRINT("  reserved	 = " << reserved << endl);
}

//===========================================================================

void BGLParser::IFINF1(Enum16  opcode,
                       SInt32 fail,
                       Var16 var,
                       Float32 low,
                       Float32 high)
{
 DEBUGPRINT("BGL_IFINF1 (" << hex << opcode << dec << "):\n");
 DEBUGPRINT("  fail	 = " << fail << endl);
 DEBUGPRINT("  var	 = 0x" << hex << var << dec << endl);
 DEBUGPRINT("  low	 = " << low << endl);
 DEBUGPRINT("  high	 = " << high << endl);
}

//===========================================================================

void BGLParser::TEXTURE_SIZE(Enum16 opcode,
                                 Float32 size)
{
 DEBUGPRINT(OPCODE_INFO[opcode].name << endl);
}

//===========================================================================

void BGLParser::VERTEX_LIST(Enum16 opcode,
                                UInt16 count,
                                UInt32 reserved,
                                const VERTEX* vertex)
{
 DEBUGPRINT(OPCODE_INFO[opcode].name << endl);
}

//===========================================================================

void BGLParser::MATERIAL_LIST(Enum16 opcode,
                                  UInt16 count,
                                  UInt32 reserved,
                                  const MATERIAL* material)
{
 DEBUGPRINT(OPCODE_INFO[opcode].name << endl);
}

//===========================================================================

void BGLParser::TEXTURE_LIST(Enum16 opcode,
                                 UInt16 count,
                                 UInt32 reserved,
                                 const TEXTURE* texture)
{
 DEBUGPRINT(OPCODE_INFO[opcode].name << endl);
}

//===========================================================================

void BGLParser::SET_MATERIAL(Enum16 opcode,
                                 UInt16 material_index,
                                 UInt16 texture_index)
{
 DEBUGPRINT(OPCODE_INFO[opcode].name << endl);
}

//===========================================================================

void BGLParser::DRAW_TRIAnglE_LIST(Enum16 opcode,
                                       UInt16 vertext_start,
                                       UInt16 vertex_count,
                                       UInt16 index_count,
                                       const UInt16* index_list)
{
 DEBUGPRINT(OPCODE_INFO[opcode].name << endl);
}

//===========================================================================

void BGLParser::DRAW_LINE_LIST(Enum16 opcode,
                                   UInt16 vertext_start,
                                   UInt16 vertex_count,
                                   UInt16 index_count,
                                   const UInt16* index_list)
{
 DEBUGPRINT(OPCODE_INFO[opcode].name << endl);
}

//===========================================================================

void BGLParser::DRAW_POINT_LIST(Enum16 opcode,
                                    UInt16 vertext_start,
                                    UInt16 vertex_count,
                                    UInt16 index_count,
                                    const UInt16* index_list)
{
 DEBUGPRINT(OPCODE_INFO[opcode].name << endl);
}

//===========================================================================

void BGLParser::BEGIN(Enum16 opcode,
                          UInt32 version)
{
 DEBUGPRINT(OPCODE_INFO[opcode].name << endl);
 cerr << "   version = " << version << endl;
}

//===========================================================================

void BGLParser::END(Enum16 opcode)
{
 DEBUGPRINT(OPCODE_INFO[opcode].name << endl);
}

//===========================================================================
