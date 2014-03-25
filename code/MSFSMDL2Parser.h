#ifndef MSFSMDL2PARSER_H
#define MSFSMDL2PARSER_H

#include "BGLParser.h"
#include "BGL.h"

namespace Assimp
{
   class MSFSMDL2Parser : public BGL::BGLParser
   {
   protected:

      BGL::UInt16 gen_model_flags_;
      float light_bias_;

      // Parameter maps
      std::map<int, BGL::ParamValue*> param_value_map_;
      std::map<int, BGL::ParamValue*> param_offset_map_;

      void initParameters();
      bool readDICT(int chunk_size);

   public:

      MSFSMDL2Parser(boost::shared_ptr<StreamReaderLE> reader);

      bool parse(aiScene* scene);

      void setLightBias(float light_bias)
      {
         light_bias_ = light_bias;
      }

      void setInputGenModel(BGL::UInt16 flags)
      {
         gen_model_flags_ = flags;
      }

      // setting of parameters
      void setPartsVisible(BGL::UInt16 vis)
      {
         param_value_map_[BGL::parts_visible]->ushort_val = vis;
      }

      void setGenModel(BGL::UInt16 vis)
      {
         param_value_map_[BGL::gen_model]->ushort_val = vis;
      }

      void setParamFloat32(int param, BGL::Float32 val)
      {
         param_value_map_[param]->float_val = val;
      }

      void setParamUInt32(int param, BGL::UInt32 val)
      {
         param_value_map_[param]->ulong_val = val;
      }

      void setParamUInt16(int param, BGL::UInt16 val)
      {
         param_value_map_[param]->ushort_val = val;
      }
   };
}
#endif // MSFSMDL2PARSER_H
