#include "MSFSMDL2Parser.h"
#include "MSFSFileData.h"
#include "Exceptional.h"

#include "AssimpPCH.h"
#include <assimp/DefaultLogger.hpp>

using namespace Assimp;
using namespace BGL;
using namespace std;

MSFSMDL2Parser::MSFSMDL2Parser(boost::shared_ptr<StreamReaderLE> reader)
   : BGLParser(reader)
{
   gen_model_flags_ = 0xffff;
   light_bias_ = 0.0f;
   initParameters();
}

//===========================================================================

void MSFSMDL2Parser::initParameters()
{
 // Base parameter block
 param_value_map_[parts_visible] = new ParamValue(Flags16_TYPE);
 param_value_map_[bomb_rocket_visible] = new ParamValue(Flags16_TYPE);
 param_value_map_[prop_visible] = new ParamValue(UInt16_TYPE);
 param_value_map_[strobe] = new ParamValue(UInt16_TYPE);
 param_value_map_[lights] = new ParamValue(UInt16_TYPE);
 param_value_map_[right_gear_b] = new ParamValue(UInt16_TYPE);
 param_value_map_[right_gear_p] = new ParamValue(UInt16_TYPE);
 param_value_map_[left_gear_b] = new ParamValue(UInt16_TYPE);
 param_value_map_[left_gear_p] = new ParamValue(UInt16_TYPE);
 param_value_map_[front_gear_p] = new ParamValue(UInt16_TYPE);
 param_value_map_[prop_pos] = new ParamValue(UInt16_TYPE);
 param_value_map_[engine_rpm] = new ParamValue(UInt16_TYPE);
 param_value_map_[rudder] = new ParamValue(UInt16_TYPE);
 param_value_map_[elevator] = new ParamValue(UInt16_TYPE);
 param_value_map_[right_flap] = new ParamValue(UInt16_TYPE);
 param_value_map_[left_flap] = new ParamValue(UInt16_TYPE);
 param_value_map_[right_aileron] = new ParamValue(UInt16_TYPE);
 param_value_map_[left_aileron] = new ParamValue(UInt16_TYPE);
 param_value_map_[gear_smoke] = new ParamValue(UInt16_TYPE);
 param_value_map_[gen_model] = new ParamValue(UInt16_TYPE);

 param_offset_map_[0x90] = param_value_map_[parts_visible];
 param_offset_map_[0x8e] = param_value_map_[bomb_rocket_visible];
 param_offset_map_[0x8c] = param_value_map_[prop_visible];
 param_offset_map_[0x8a] = param_value_map_[strobe];
 param_offset_map_[0x88] = param_value_map_[lights];
 param_offset_map_[0x86] = param_value_map_[right_gear_b];
 param_offset_map_[0x84] = param_value_map_[right_gear_p];
 param_offset_map_[0x82] = param_value_map_[left_gear_b];
 param_offset_map_[0x80] = param_value_map_[left_gear_p];
 param_offset_map_[0x7e] = param_value_map_[front_gear_p];
 param_offset_map_[0x7c] = param_value_map_[prop_pos];
 param_offset_map_[0x7a] = param_value_map_[engine_rpm];
 param_offset_map_[0x78] = param_value_map_[rudder];
 param_offset_map_[0x76] = param_value_map_[elevator];
 param_offset_map_[0x74] = param_value_map_[right_flap];
 param_offset_map_[0x72] = param_value_map_[left_flap];
 param_offset_map_[0x70] = param_value_map_[right_aileron];
 param_offset_map_[0x6e] = param_value_map_[left_aileron];
 param_offset_map_[0x6c] = param_value_map_[gear_smoke];
 param_offset_map_[0x68] = param_value_map_[gen_model];


 // DICT Parameter block
 param_value_map_[l_gear] = new ParamValue(Float32_TYPE);
 param_value_map_[r_gear] = new ParamValue(Float32_TYPE);
 param_value_map_[c_gear] = new ParamValue(Float32_TYPE);
 param_value_map_[r_spoiler] = new ParamValue(Float32_TYPE);
 param_value_map_[l_spoiler] = new ParamValue(Float32_TYPE);
 param_value_map_[r_thrust_rev] = new ParamValue(Float32_TYPE);
 param_value_map_[l_thrust_rev] = new ParamValue(Float32_TYPE);
 param_value_map_[nnumber] = new ParamValue(STRING_TYPE);
 param_value_map_[color_nnumber] = new ParamValue(UInt32_TYPE);
 param_value_map_[font_nnumber] = new ParamValue(STRING_TYPE);
 param_value_map_[visor] = new ParamValue(Float32_TYPE);
 param_value_map_[concorde_nose] = new ParamValue(Float32_TYPE);
 param_value_map_[engine0] = new ParamValue(UInt32_TYPE);
 param_value_map_[engine1] = new ParamValue(UInt32_TYPE);
 param_value_map_[engine2] = new ParamValue(UInt32_TYPE);
 param_value_map_[engine3] = new ParamValue(UInt32_TYPE);
 param_value_map_[prop_pos0] = new ParamValue(UInt16_TYPE);
 param_value_map_[prop_pos1] = new ParamValue(UInt16_TYPE);
 param_value_map_[prop_rpm0] = new ParamValue(UInt16_TYPE);
 param_value_map_[prop_rpm1] = new ParamValue(UInt16_TYPE);
 param_value_map_[trimtab_elevator] = new ParamValue(UInt16_TYPE);
 param_value_map_[trimtab_l_aileron] = new ParamValue(UInt16_TYPE);
 param_value_map_[trimtab_r_aileron] = new ParamValue(UInt16_TYPE);
 param_value_map_[trimtab_rudder] = new ParamValue(UInt16_TYPE);
 param_value_map_[rudder_water_rotate] = new ParamValue(Float32_TYPE);
 param_value_map_[elevon0L] = new ParamValue(UInt16_TYPE);
 param_value_map_[elevon1L] = new ParamValue(UInt16_TYPE);
 param_value_map_[elevon2L] = new ParamValue(UInt16_TYPE);
 param_value_map_[elevon3R] = new ParamValue(UInt16_TYPE);
 param_value_map_[elevon4R] = new ParamValue(UInt16_TYPE);
 param_value_map_[elevon5R] = new ParamValue(UInt16_TYPE);
 param_value_map_[c_wheel] = new ParamValue(Float32_TYPE);
 param_value_map_[g_lightStates] = new ParamValue(UInt32_TYPE);
 param_value_map_[crash_check] = new ParamValue(UInt16_TYPE);
 param_value_map_[l_wingfold] = new ParamValue(Float32_TYPE);
 param_value_map_[r_wingfold] = new ParamValue(Float32_TYPE);
 param_value_map_[l_pontoon] = new ParamValue(Float32_TYPE);
 param_value_map_[r_pontoon] = new ParamValue(Float32_TYPE);
 param_value_map_[cowling] = new ParamValue(Float32_TYPE);
 param_value_map_[f_canopy] = new ParamValue(Float32_TYPE);
 param_value_map_[r_canopy] = new ParamValue(Float32_TYPE);
 param_value_map_[vc_f_canopy] = new ParamValue(Float32_TYPE);
 param_value_map_[vc_r_canopy] = new ParamValue(Float32_TYPE);
 param_value_map_[Door_Passenger] = new ParamValue(Float32_TYPE);
 param_value_map_[Door_Cargo] = new ParamValue(Float32_TYPE);
 param_value_map_[pilot] = new ParamValue(Float32_TYPE);
 param_value_map_[gunner0] = new ParamValue(Float32_TYPE);
 param_value_map_[gunner1] = new ParamValue(Float32_TYPE);
 param_value_map_[gunner2] = new ParamValue(Float32_TYPE);
 param_value_map_[tailhook] = new ParamValue(Float32_TYPE);
 param_value_map_[l_flap_key] = new ParamValue(Float32_TYPE);
 param_value_map_[r_flap_key] = new ParamValue(Float32_TYPE);
 param_value_map_[userdefined0] = new ParamValue(Float32_TYPE);
 param_value_map_[userdefined1] = new ParamValue(Float32_TYPE);
 param_value_map_[userdefined2] = new ParamValue(Float32_TYPE);
 param_value_map_[userdefined3] = new ParamValue(Float32_TYPE);
 param_value_map_[userdefined4] = new ParamValue(Float32_TYPE);
 param_value_map_[userdefined5] = new ParamValue(Float32_TYPE);
 param_value_map_[userdefined6] = new ParamValue(Float32_TYPE);
 param_value_map_[userdefined7] = new ParamValue(Float32_TYPE);
 param_value_map_[userdefined8] = new ParamValue(Float32_TYPE);
 param_value_map_[rudder_water_deploy] = new ParamValue(Float32_TYPE);
 param_value_map_[mount0] = new ParamValue(GUid_TYPE);
 param_value_map_[mount1] = new ParamValue(GUid_TYPE);
 param_value_map_[mount2] = new ParamValue(GUid_TYPE);
 param_value_map_[mount3] = new ParamValue(GUid_TYPE);
 param_value_map_[mount4] = new ParamValue(GUid_TYPE);
 param_value_map_[mount5] = new ParamValue(GUid_TYPE);
 param_value_map_[mount6] = new ParamValue(GUid_TYPE);
 param_value_map_[mount7] = new ParamValue(GUid_TYPE);
 param_value_map_[mount8] = new ParamValue(GUid_TYPE);
 param_value_map_[mount9] = new ParamValue(GUid_TYPE);
 param_value_map_[mount10] = new ParamValue(GUid_TYPE);
 param_value_map_[bomb_bay] = new ParamValue(Float32_TYPE);
 param_value_map_[endcaps1] = new ParamValue(Flags16_TYPE);
 param_value_map_[endcaps2] = new ParamValue(Flags16_TYPE);
 param_value_map_[c_tire] = new ParamValue(UInt32_TYPE);
 param_value_map_[l_tire] = new ParamValue(UInt32_TYPE);
 param_value_map_[r_tire] = new ParamValue(UInt32_TYPE);
 param_value_map_[gun0] = new ParamValue(UInt16_TYPE);
 param_value_map_[gun1] = new ParamValue(UInt16_TYPE);
 param_value_map_[gun2] = new ParamValue(UInt16_TYPE);
 param_value_map_[gun3] = new ParamValue(UInt16_TYPE);
 param_value_map_[gun4] = new ParamValue(UInt16_TYPE);
 param_value_map_[gun5] = new ParamValue(UInt16_TYPE);
 param_value_map_[gun6] = new ParamValue(UInt16_TYPE);
 param_value_map_[gun7] = new ParamValue(UInt16_TYPE);
 param_value_map_[gun8] = new ParamValue(UInt16_TYPE);
 param_value_map_[gun9] = new ParamValue(UInt16_TYPE);
 param_value_map_[gun10] = new ParamValue(UInt16_TYPE);
 param_value_map_[gun11] = new ParamValue(UInt16_TYPE);
 param_value_map_[gun12] = new ParamValue(UInt16_TYPE);
 param_value_map_[gun13] = new ParamValue(UInt16_TYPE);
 param_value_map_[gun14] = new ParamValue(UInt16_TYPE);
 param_value_map_[gun15] = new ParamValue(UInt16_TYPE);
 param_value_map_[barrel0] = new ParamValue(UInt16_TYPE);
 param_value_map_[barrel1] = new ParamValue(UInt16_TYPE);
 param_value_map_[barrel2] = new ParamValue(UInt16_TYPE);
 param_value_map_[barrel3] = new ParamValue(UInt16_TYPE);
 param_value_map_[barrel4] = new ParamValue(UInt16_TYPE);
 param_value_map_[barrel5] = new ParamValue(UInt16_TYPE);
 param_value_map_[barrel6] = new ParamValue(UInt16_TYPE);
 param_value_map_[barrel7] = new ParamValue(UInt16_TYPE);
 param_value_map_[barrel8] = new ParamValue(UInt16_TYPE);
 param_value_map_[barrel9] = new ParamValue(UInt16_TYPE);
 param_value_map_[barrel10] = new ParamValue(UInt16_TYPE);
 param_value_map_[barrel11] = new ParamValue(UInt16_TYPE);
 param_value_map_[barrel12] = new ParamValue(UInt16_TYPE);
 param_value_map_[barrel13] = new ParamValue(UInt16_TYPE);
 param_value_map_[barrel14] = new ParamValue(UInt16_TYPE);
 param_value_map_[barrel15] = new ParamValue(UInt16_TYPE);
 param_value_map_[damaged0] = new ParamValue(Flags16_TYPE);
 param_value_map_[bullets0] = new ParamValue(Flags16_TYPE);
 param_value_map_[bullets1] = new ParamValue(Flags16_TYPE);
 param_value_map_[bullets2] = new ParamValue(Flags16_TYPE);
 param_value_map_[bullets3] = new ParamValue(Flags16_TYPE);
 param_value_map_[bullets4] = new ParamValue(Flags16_TYPE);
 param_value_map_[bullets5] = new ParamValue(Flags16_TYPE);
 param_value_map_[bullets6] = new ParamValue(Flags16_TYPE);
 param_value_map_[bullets7] = new ParamValue(Flags16_TYPE);
 param_value_map_[pylon] = new ParamValue(UInt16_TYPE);
 param_value_map_[cockpit_detail] = new ParamValue(UInt16_TYPE);
 param_value_map_[battery_switch] = new ParamValue(Float32_TYPE);
 param_value_map_[l_pct_lead_edge_flap0] = new ParamValue(Float32_TYPE);
 param_value_map_[r_pct_lead_edge_flap0] = new ParamValue(Float32_TYPE);
 param_value_map_[l_pct_lead_edge_flap1] = new ParamValue(Float32_TYPE);
 param_value_map_[r_pct_lead_edge_flap1] = new ParamValue(Float32_TYPE);
 param_value_map_[l_pct_trail_edge_flap0] = new ParamValue(Float32_TYPE);
 param_value_map_[r_pct_trail_edge_flap0] = new ParamValue(Float32_TYPE);
 param_value_map_[l_pct_trail_edge_flap1] = new ParamValue(Float32_TYPE);
 param_value_map_[r_pct_trail_edge_flap1] = new ParamValue(Float32_TYPE);
 param_value_map_[thrust_reverser0] = new ParamValue(Float32_TYPE);
 param_value_map_[thrust_reverser1] = new ParamValue(Float32_TYPE);
 param_value_map_[thrust_reverser2] = new ParamValue(Float32_TYPE);
 param_value_map_[thrust_reverser3] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_throttle0] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_throttle1] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_throttle2] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_throttle3] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_prop_pitch0] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_prop_pitch1] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_prop_pitch2] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_prop_pitch3] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_mixture0] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_mixture1] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_mixture2] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_mixture3] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_water_rudder] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_stick_fore_aft] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_stick_l_r] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_pedals_l_r] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_collective] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_landing_gear] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_speed_brake] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_parking_brake] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_flap] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_cowl_flaps0] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_cowl_flaps1] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_cowl_flaps2] = new ParamValue(Float32_TYPE);
 param_value_map_[lever_cowl_flaps3] = new ParamValue(Float32_TYPE);
 param_value_map_[cowl_flaps0] = new ParamValue(Float32_TYPE);
 param_value_map_[cowl_flaps1] = new ParamValue(Float32_TYPE);
 param_value_map_[cowl_flaps2] = new ParamValue(Float32_TYPE);
 param_value_map_[cowl_flaps3] = new ParamValue(Float32_TYPE);
 param_value_map_[aux_gear] = new ParamValue(Float32_TYPE);
}

//===========================================================================

bool MSFSMDL2Parser::readDICT(int chunk_size)
{
 int num_dict = chunk_size / sizeof(DICT_PARAM);

 for(int i = 0; i < num_dict; i++)
    {
    DICT_PARAM p;
    p.uType = reader_->GetU4();
    p.uOffset = reader_->GetU4();
    p.uLen = reader_->GetU4();

    readBytes((char*)p.guidParam.g1, 4);
    readBytes((char*)p.guidParam.g2, 2);
    readBytes((char*)p.guidParam.g3, 2);
    readBytes((char*)p.guidParam.g4, 2);
    readBytes((char*)p.guidParam.g5, 6);

#ifdef DEBUG
    switch(p.uType)
       {
       case Float32_TYPE:
          cerr << "Float32: 0x";
          break;

       case UInt32_TYPE:
          cerr << "UInt32 : 0x";
          break;

       case STRING_TYPE:
          cerr << "STRING : 0x";
          break;

       case UInt16_TYPE:
          cerr << "UInt16 : 0x";
          break;

       case Flags16_TYPE:
          cerr << "Flags16: 0x";
          break;

       default:
          cerr << "(unknown type)\n";
          break;
       }
#endif
    cerr << hex << p.uOffset << ", " << dec << p.uLen << ", ";
    cerr << hex;
    char guid_str[64];
    sprintf(guid_str, "%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X",
            p.guidParam.g1[3],
            p.guidParam.g1[2],
            p.guidParam.g1[1],
            p.guidParam.g1[0],
            p.guidParam.g2[1],
            p.guidParam.g2[0],
            p.guidParam.g3[1],
            p.guidParam.g3[0],
            p.guidParam.g4[0],
            p.guidParam.g4[1],
            p.guidParam.g5[0],
            p.guidParam.g5[1],
            p.guidParam.g5[2],
            p.guidParam.g5[3],
            p.guidParam.g5[4],
            p.guidParam.g5[5]);

    cerr << "GUid: " << guid_str << endl;

    if(p.uType == GUid_TYPE)
       continue;

    // Map GUid to variable
    for(int i = 0; i < NUM_AIRCRAFT_PARAMS; i++)
       {
       if(strcmp(guid_str, AIRCRAFT_PARAMS[i].guid_str) == 0)
          {
          ParamValue* val = param_value_map_[AIRCRAFT_PARAMS[i].name];
          cerr << AIRCRAFT_PARAMS[i].name_str << " = " << p.uOffset << endl;
          val->param_name = AIRCRAFT_PARAMS[i].name_str;
          param_offset_map_[p.uOffset] = val;
          if(val->type == UInt32_TYPE)
             param_offset_map_[p.uOffset+2] = val;
          break;
          }
       }
    }

 return true;
}

//===========================================================================

bool MSFSMDL2Parser::parse(aiScene *scene)
{
   UInt32 magic = readFourCC();
   UInt32 debug1 = (UInt32)AI_MSFS_FOURCC_RIFF;
   UInt32 debug2 = (UInt32)AI_MSFS_FOURCC_MDL8;
   UInt32 debug3 = (UInt32)AI_MSFS_FOURCC_MDLH;

   if(magic != AI_MSFS_FOURCC_RIFF)
      throw DeadlyImportError("MSFS: Not a RIFF file");

   UInt32 file_sz = reader_->GetU4();

   magic = readFourCC();
   if(magic != AI_MSFS_FOURCC_MDL8)
      throw DeadlyImportError("MSFS: Not an MSFS MDL file");

   long bgl_start = -1;
   bool got_dict  = false;
   bool got_hdr   = false;

   while(reader_->GetRemainingSize() > 0)
   {
      magic = readFourCC();
      UInt32 chunk_sz = reader_->GetU4();

      if(magic == AI_MSFS_FOURCC_MDLH)
      {
         reader_->IncPtr(chunk_sz);
         got_hdr = true;
      }
      else if(magic == AI_MSFS_FOURCC_DICT)
      {
         readDICT(chunk_sz);
         got_dict = true;
      }
      else if(magic == AI_MSFS_FOURCC_BGL)
      {
         bgl_start = reader_->GetCurrentPos();
         reader_->IncPtr(chunk_sz);
      }
      else
      {
         cerr << "unknown chunk '" << magic << "' - skipping\n";
         reader_->IncPtr(chunk_sz);
      }

      if(bgl_start >= 0 && got_dict && got_hdr)
         break;
   }

   // Set up some parts
   setParamFloat32(c_gear, 200.0f);
   setParamFloat32(l_gear, 200.0f);
   setParamFloat32(r_gear, 200.0f);
   setParamUInt32(c_tire, 100);
   setParamFloat32(l_spoiler, 100.0f);
   setParamFloat32(r_spoiler, 100.0f);
   setParamFloat32(lever_speed_brake, 100.0f);
   setParamFloat32(f_canopy, 100.0f);
   setParamFloat32(r_canopy, 100.0f);
  // setParamUInt16(prop_visible, 0);

  // setParamUInt16(engine_rpm, 2000);
  // setParamUInt16(prop_rpm0, 2000);
  // setParamUInt16(prop_rpm1, 2000);

  // setParamFloat32(userdefined8, 100.0f);

   // Hack!
  // param_offset_map_[0xf6] = new ParamValue(UInt16_TYPE);
  // param_offset_map_[0xf6]->ushort_val = 10000;

   setPartsVisible(0xffff);

   setParamUInt16(cockpit_detail, 0xffff);
   setParamUInt32(g_lightStates, 0xffffffff);

   setGenModel(gen_model_flags_);
   if(bgl_start < 0)
      {
      cerr << "No BGL chunk found!\n";
      return NULL;
      }

   // Seek to start of BGL Code:
   reader_->SetCurrentPos(bgl_start);

   // Parse opcodes
   while(reader_->GetRemainingSize() > 0 && !done_)
   {
      UInt16 opcode = reader_->GetU2();
      parseOpcode(opcode);
   }

   return true;
}
