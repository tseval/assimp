#ifndef BGL_H
#define BGL_H

#include <iostream>

namespace Assimp {
namespace BGL
{
   // basic types.
   typedef	unsigned	char	UInt8, *PUInt8, **PPUInt8;
   typedef	signed		char	SInt8, *PSInt8, **PSSInt8;
   typedef	unsigned	short	UInt16, *PUInt16, **PPUInt16;
   typedef	signed		short	SInt16, *PSInt16, **PSSInt16;
   typedef	signed		int	SInt32, *PSInt32, **PSSInt32;
   typedef	unsigned	int	UInt32, *PUInt32, **PPUInt32;
   typedef	unsigned	char	Var8, *PVar8, **PPVar8;
   typedef	unsigned	short	Var16, *PVar16, **PPVar16;
   typedef	signed		int	Var32, *PVar32, **PPVar32;

   struct GUid128
   {
      unsigned char guid[16];
   };

   // SInt48 is defined later, after Angl48

   // 64-bit generic structure
   typedef struct Var64
   {
      Var32	lo;
      Var32	hi;
   } Var64, *PVar64, **PPVar64;

   typedef struct SInt64
   {
      UInt32	lo;
      SInt32	hi;
   } SInt64, *PSInt64, **PSSInt64;

   // boolean variables - hold TRUE/FALSE
   typedef	int		Bool, *PBool, **PPBool;
   typedef	Var8	Bool8, *PBool8, **PPBool8;
   typedef	Var16	Bool16, *PBool16, **PPBool16;
   typedef	Var32	Bool32, *PBool32, **PPBool32;

   // array of 1-bit boolean variables
   typedef int		Flags, *PFlags, **PPFlags;
   typedef Var8	Flags8, *PFlags8, **PPFlags8;
   typedef Var16	Flags16, *PFlags16, **PPFlags16;
   typedef Var32	Flags32, *PFlags32, **PPFlags32;

   // Enumeration variables - domain is subset of all possible values
   typedef int		Enum, *PEnum, **PPEnum;
   typedef Var8	Enum8, *PEnum8, **PPEnum8;
   typedef Var16	Enum16, *PEnum16, **PPEnum16;
   typedef Var32	Enum32, *PEnum32, **PPEnum32;

   // Identifier variables
   /*
   typedef int		ID, *PID, **PPID;
   typedef Var8	ID8, *PID8, **PPID8;
   typedef Var16	ID16, *PID16, **PPID16;
   typedef Var32	ID32, *PID32, **PPID32;
   */

   // Error return variables
   typedef	Var32	ERR, *PERR, **PPERR;

   // Fractional variables
   typedef UInt8	UFRAC8, *PUFRAC8, **PPUFRAC8;	 // { 0..+1}
   typedef SInt8	SFRAC8, *PSFRAC8, **PPSFRAC8;	 // {-1..+1}
   typedef UInt16	UFRAC16, *PUFRAC16, **PPUFRAC16; // { 0..+1}
   typedef SInt16	SFRAC16, *PSFRAC16, **PPSFRAC16; // {-1..+1}
   typedef UInt32	UFRAC32, *PUFRAC32, **PPUFRAC32; // { 0..+1}
   typedef SInt32	SFRAC32, *PSFRAC32, **PPSFRAC32; // {-1..+1}

   // Integer/Fraction structures
   typedef	UInt16	UIF16, *PUIF16, **PPUIF16;
   typedef	SInt16	SIF16, *PSIF16, **PPSIF16;
   typedef struct	UIF48
   {
      UInt16	pad;
      UInt16	f;
      UInt32	i;
   } UIF48, *PUIF48, **PPUIF48;

   typedef	UInt32	UIF32, *PUIF32, **PPUIF32;
   typedef	SInt32	SIF32, *PSIF32, **PPSIF32;
   typedef struct	SIF48
   {
      UInt16	pad;
      UInt16	f;
      SInt32	i;
   } SIF48, *PSIF48, **PPSIF48;

   typedef SInt64	SIF64, *PSIF64, **PPSIF64;

   // Floating-point types
   typedef float	Float32, *PFloat32, **PPFloat32;
   typedef double	Float64, *PFloat64, **PPFloat64;

   typedef char	STRING, *PSTRING, **PPSTRING;		// generic string of unknown length
   typedef char	STRINGZ, *PSTRINGZ, **PPSTRINGZ;	// generic string of unknown length, zero term

   typedef Var16	BCD16, *PBCD16, **PPBCD16;		// 4-digit BCD number (0000-9999)
   typedef Var16	BCO16, *PBCO16, **PPBCO16;		// 4-digit Octal number (0000-7777) (in BCD)
   typedef	Var32	BCD32, *PBCD32, **PPBCD32;		// 8-digit BCD number (00000000-99999999)

   // pseudodegree variables
   typedef Var8	Angl8, *PAngl8, **PPAngl8;
   typedef Var16	Angl16, *PAngl16, **PPAngl16;
   typedef Var32	Angl32, *PAngl32, **PPAngl32;
   typedef struct	Angl48
   {
      UInt16	pad;
      UInt16	lo;
      UInt32	hi;
   } Angl48, *PAngl48, **PPAngl48;

   typedef	Angl48	SInt48, *PSInt48, **PSSInt48;

   //	2D data structures
   typedef SInt32	PIXEL, *PPIXEL, **PPPIXEL;		// screen pixel

   typedef struct	PIXPOINT
   {
      PIXEL x;
      PIXEL y;
   } PIXPOINT, *PPIXPOINT, **PPPIXPOINT;

   typedef struct	PIXBOX
   {
      PIXEL x;
      PIXEL y;
      PIXEL size_x;
      PIXEL size_y;
   } PIXBOX, *PPIXBOX, **PPPIXBOX;

   struct LLA
   {
      SIF48	lat;
      Angl48	lon;
      SIF48	alt;
   };

   struct XZ16
   {
      SInt16 x, z;
   };

   struct XYZ16
   {
      SInt16 x, y, z;
   };

   struct XYZF32
   {
      Float32 x, y, z;
   };

   struct PBH16
   {
      SInt16 pitch, bank, heading;
   };

   struct LATLONALTPBH
   {
      LLA 	lla;
      PBH16 	pbh;
   };

   struct PXZ16
   {
      UInt16 p;  // reserve point index of a point
      SInt16 tx; // texture X coordinate (256 = 1.0)
      SInt16 tz; // texture Z coordinate (256 = 1.0)
   };

   struct GVERTEX
   {
      SInt16 x;  // vertex X value
      SInt16 y;  // vertex Y value
      SInt16 z;  // vertex Z value
      SInt16 nx; // normal X value
      SInt16 ny; // normal Y value
      SInt16 nz; // normal Z value
   };

   struct VERTEX
   {
      Float32 x, y, z;		///< Vertex coordinate
      Float32 nx, ny, nz;	///< Normal vector
      Float32 tu, tv;		///< Texture coordinate
   };

   struct UNICOL
   {
      Var8 r, g, b, a;
   };

   struct MATERIAL
   {
      Float32 diffuse_r;  ///< Diffuse color.
      Float32 diffuse_g;
      Float32 diffuse_b;
      Float32 diffuse_a;

      Float32 ambient_r;  ///< Ambient color.
      Float32 ambient_g;
      Float32 ambient_b;
      Float32 ambient_a;  ///<  Must be 1.0.

      Float32 specular_r; ///<  Specular color.
      Float32 specular_g;
      Float32 specular_b;
      Float32 specular_a; ///< Must be 1.0.

      Float32 emissive_r; ///< Emissive color.
      Float32 emissive_g;
      Float32 emissive_b;
      Float32 emissive_a; ///< Must be 1.0.

      Float32 power;      ///< Specular power.
   };

   struct TEXTURE
   {
      UInt32 cat;		///<  Class/type of texture, see the  Texture category values  section below.
      UInt32 color;		///<  Fallback color (B G R A ).
      UInt32 reserved;		///<  Reserved variable and MUST BE 0.
      Float32 texture_size; 	///<  Size in meters of texture, used for mip selection.
      STRINGZ tname[64]; 	///<  Texture name ASCIIZ string.
   };

   /** Texture category values.
    * <h3>Notes</h3>
    * <ul>
    * <li> If the next texture entry has a category = TEXTURE2_* then
    * the entry is considered part of the first entry and it is used as
    * a multitexture.
    * <li> When using a ReflectMap the texture name must be the same as
    * the base texture.
    * </ul>
    */
   enum TEXTURE_CATEGORY
      {
      TEXTURE_AIRCRAFT    = 1, 		///< Aircraft texture.
      TEXTURE_BUILDING    = 6,		///< Scenery texture.
      TEXTURE2_NIGHT      = 0x100, 	///< NightMap texture used at nighttime.
      TEXTURE2_REFLECT    = 0x200, 	///< ReflectMap.
      TEXTURE2_LIGHTMAP   = 0x300, 	///< LightMap.
      TEXTURE2_LIGHTMAP_A = 0x400 	///< LightMap with AlphaMask.
      };

   enum FS_VERSION
      {
      CFS2   = 0x732,
      FS2002 = 0x800,
      };

   enum BUILDING_TYPE
      {
      BUILD_RECT_FLAT_ROOF_T = 4,
      BUILD_RECT_RIDGE_ROOF_T = 6,
      BUILD_RECT_PEAK_ROOF_T = 7,
      BUILD_RECT_SLANT_ROOF_T = 8,
      BUILD_PYRAMID_T = 9,
      BUILD_N_SIDED_T = 10,
      BUILD_OCTAGONAL_T = 11
      };

   struct BUILD_RECT_FLAT_ROOF_S
   {
      UInt16 size_x;
      UInt16 size_z;
      UInt16 bottom_texture;
      UInt16 size_bot_y;
      UInt16 tindex_bot_x;
      UInt16 tindex_bot_z;
      UInt16 window_texture;
      UInt16 size_win_y;
      UInt16 tindex_win_x;
      UInt16 tindex_win_y;
      UInt16 tindex_win_z;
      UInt16 top_texture;
      UInt16 size_top_y;
      UInt16 tindex_top_x;
      UInt16 tindex_top_z;
      UInt16 roof_texture;
      UInt16 tindex_roof_x;
      UInt16 tindex_roof_z;
   };

   struct BUILD_RECT_RIDGE_ROOF_S
   {
      UInt16 size_x;
      UInt16 size_z;
      UInt16 bottom_texture;

      UInt16 size_bot_y;
      UInt16 tindex_bot_x;
      UInt16 tindex_bot_z;

      UInt16 window_texture;
      UInt16 size_win_y;

      UInt16 tindex_win_x;
      UInt16 tindex_win_y;
      UInt16 tindex_win_z;

      UInt16 top_texture;
      UInt16 size_top_y;
      UInt16 tindex_top_x;
      UInt16 tindex_top_z;

      UInt16 roof_texture;
      UInt16 tindex_roof_x;
      UInt16 tindex_roof_z;

      UInt16 size_roof_y;
      UInt16 tindex_gable_y;
      UInt16 gable_texture;
      UInt16 tindex_gable_z;
   };

   struct BUILD_RECT_PEAK_ROOF_S
   {
      UInt16 size_x;
      UInt16 size_z;
      UInt16 bottom_texture;

      UInt16 size_bot_y;
      UInt16 tindex_bot_x;
      UInt16 tindex_bot_z;

      UInt16 window_texture;
      UInt16 size_win_y;

      UInt16 tindex_win_x;
      UInt16 tindex_win_y;
      UInt16 tindex_win_z;

      UInt16 top_texture;
      UInt16 size_top_y;
      UInt16 tindex_top_x;
      UInt16 tindex_top_z;

      UInt16 roof_texture;
      UInt16 tindex_roof_x;
      UInt16 tindex_roof_z;

      UInt16 size_roof_y;
      UInt16 tindex_roof_y;
   };

   struct BUILD_RECT_SLANT_ROOF_S
   {
      UInt16 size_x;
      UInt16 size_z;
      UInt16 bottom_texture;

      UInt16 size_bot_y;
      UInt16 tindex_bot_x;
      UInt16 tindex_bot_z;

      UInt16 window_texture;
      UInt16 size_win_y;

      UInt16 tindex_win_x;
      UInt16 tindex_win_y;
      UInt16 tindex_win_z;

      UInt16 top_texture;
      UInt16 size_top_y;
      UInt16 tindex_top_x;
      UInt16 tindex_top_z;

      UInt16 roof_texture;
      UInt16 tindex_roof_x;
      UInt16 tindex_roof_z;

      UInt16 size_roof_y;
      UInt16 tindex_gable_y;
      UInt16 gable_texture;
      UInt16 tindex_gable_z;

      UInt16 face_texture;
      UInt16 tindex_face_x;
      UInt16 tindex_face_y;
   };

   struct BUILD_PYRAMID_S
   {
      UInt16 base_size_x;
      UInt16 base_size_z;
      UInt16 top_size_x;
      UInt16 top_size_z;
      UInt16 bottom_texture;

      UInt16 size_bot_y;
      UInt16 tindex_bot_x;
      UInt16 tindex_bot_z;

      UInt16 window_texture;
      UInt16 size_win_y;

      UInt16 tindex_win_x;
      UInt16 tindex_win_y;
      UInt16 tindex_win_z;

      UInt16 top_texture;
      UInt16 size_top_y;
      UInt16 tindex_top_x;
      UInt16 tindex_top_z;

      UInt16 roof_texture;
      UInt16 tindex_roof_x;
      UInt16 tindex_roof_z;
   };

   struct BUILD_MULTI_SIDED_S
   {
      UInt8  sides;
      UInt8  spare;

      UInt16 size_x;
      UInt16 size_z;
      UInt16 bottom_texture;

      UInt16 size_bot_y;
      UInt16 tindex_bot_x;
      UInt16 tindex_bot_z;

      UInt16 window_texture;
      UInt16 size_win_y;

      UInt16 tindex_win_x;
      UInt16 tindex_win_y;
      UInt16 tindex_win_z;

      UInt16 top_texture;
      UInt16 size_top_y;
      UInt16 tindex_top_x;
      UInt16 tindex_top_z;

      UInt16 roof_texture;
      UInt16 size_roof_y;
      UInt16 tindex_roof_x;
      UInt16 tindex_roof_z;
   };

   struct FILE_HEADER
   { 			// PRE-FLIGHT SIMULATOR 7.0 BGL file header
      Var16 FL_world_set; 	// 00 world set number
      SInt32 FL_north_bounds; 	// 02 north bounds (NSEW bounds)
      SInt32 FL_south_bounds; 	// 06 south bound
      Angl32 FL_east_bounds; 	// 10 east bound
      Angl32 FL_west_bounds; 	// 14 west bound
      UInt32 FL_vor_ptr; 	// 18 VOR data
      Var16 FL_vor_lo; 		// 22 lowest vor freq (channel 0-199
      Var16 FL_vor_hi; 		// 24 highest vor freq (108.00-117.95
      UInt32 FL_seed_ptrs[7]; 	// 26 seeds level 8-14
      UInt32 FL_seed_15; 	// 54 seed level 15
      UInt32 FL_object_ptr; 	// 58 OBJECT data
      UInt32 FL_library_ptr; 	// 62 LIBRARY data
      UInt32 FL_facilities_ptr; // 66 FACILITIES data
      UInt32 FL_anchor_data; 	// 70 ANCHOR POINT data
      UInt32 FL_com_data; 	// 74 COM RADIO data
      UInt32 FL_adf_data; 	// 78 ADF data
      UInt32 FL_dynamic_data; 	// 82 DYNAMIC data
      SInt64 FL_library_min; 	// 86 Library id min
      SInt64 FL_library_max; 	// 94 Library id max
      UInt32 FL_misc_data; 	//102 MISC data (ground alt db)
      UInt32 FL_title; 		//106 TITLE AND DESCRIPTION
      UInt32 FL_magvar; 	//110 MAGVar data
      UInt32 FL_exceptions; 	//114 EXCEPTION LIST data
      UInt32 FL_magic; 		//118 magic number
      Var32 FL_spare2; 		//122
      Var16 FL_spare3; 		//126
   };


   struct FILE_HEADER2
   { 			// FLIGHT SIMULATOR 7.00 BGL file header
      Var16 FL_world_set; 	// 00 world set number (unused)
      SInt32 FL_north_bounds; 	// 02 north bounds (NSEW bounds)
      SInt32 FL_south_bounds; 	// 06 south bound
      Angl32 FL_east_bounds; 	// 10 east bound
      Angl32 FL_west_bounds; 	// 14 west bound
      UInt32 FL_vor_ptr; 	// 18 VOR data
      Var16 FL_vor_lo; 		// 22 lowest vor freq (channel 0-199)
      Var16 FL_vor_hi; 		// 24 highest vor freq (108.00-117.95
      UInt32 FL_free[6]; 	// 26 (MUST BE 0)
      UInt32 FL_msa_data; 	// 50 Minimum Safe Altitude Data
      UInt32 FL_terrain_data; 	// 54 new terrain data
      UInt32 FL_object_ptr; 	// 58 OBJECT data
      UInt32 FL_library_ptr; 	// 62 LIBRARY data
      UInt32 FL_facilities_ptr; // 66 FACILITIES data
      UInt32 FL_free_70; 	// 70 (MUST BE 0)
      UInt32 FL_free_74; 	// 74 (MUST BE 0)
      UInt32 FL_adf_data; 	// 78 ADF data
      UInt32 FL_dynamic_data; 	// 82 DYNAMIC data
      SInt64 FL_library_min; 	// 86 Library id min
      SInt64 FL_library_max; 	// 94 Library id max
      UInt32 FL_misc_data; 	//102 MISC data (ground alt db)
      UInt32 FL_title; 		//106 TITLE AND DESCRIPTION
      UInt32 FL_magvar; 	//110 MAGVar data
      UInt32 FL_exceptions; 	//114 EXCEPTION LIST data
      UInt32 FL_magic; 		//118 magic number (0x87654321)
      Var32 FL_spare2; 		//122
      Var16 FL_spare3; 		//126
      GUid128 FL_guid; 		//128 GUid
      UInt32 FL_product_id; 	//144 PRODUCT ID
      UInt32 FL_build_num; 	//148 PRODUCT BUILD NUMBER
      UInt32 FL_ptr_count; 	//152 data pointers count
      UInt32 FL_facility2_name_list; //156 facility2 name list
      UInt32 FL_facility2_band_list; //160 facility2 latband list
      UInt32 FL_facility2_data; //164 facility2 object list
   };

   struct FE_LATBAND_REL
   {
      Enum8	opcode;
      SInt16	latmin;
      SInt16	latmax;
      SInt32	band_ofs;
   };

   struct LARGE_OBJECT_HEADER
   {
      Enum8	opcode;
      SInt32	latitude;
      UInt32	longitude;
      Var8	img_power;
      Var16	bytecount;
   };

   /** Runway markings bit mask.
    * This 16-bit word contains information about one
    * single runway as given in the RUNWAY_BASE() command.
    * \see NEW_RUNWAY
    * \see RUNWAY_BASE
    */
   struct RWY_MARKINGS
   {
      Flags16 	edges:1;	///< bit 0 = there are painted edge lines
      Flags16	threshold:1;	///< bit 1 = there are threshold markings
      Flags16	touchdown:1;	///< bit 2 = there are touchdown markings
      Flags16	fixed:1;	///< bit 3 = there are fixed distance markings
      Flags16	dashes:1;	///< bit 4 = there are center line dashes
      Flags16	ident:1;	///< bit 5 = there are runway numbers and designations
      Flags16	precision:1;	///< bit 6 = there are precision markings
      Flags16	edge_pavement:1;///< bit 7 = there is pavement beyond the edge markings
      Flags16	spares:3;	///< bits 8-10 = spares and MUST BE 0
      Flags16	single_end:1;	///< bit 11 = this runway has only one usable end (base end) and the reciprocal end is unused and has no markings
      Flags16	base_closed:1;	///< bit 12 = this runway s base end is closed and will have no ident or threshold marking and will be marked with an  X
      Flags16	recip_closed:1; ///< bit 13 = this runway s reciprocal end is closed and will have no ident or threshold marking and will be marked with an  X
      Flags16	base_stol:1;	///< bit 14 = this runway s base end is Short Take Off and Landing and will have no threshold marking and will be marked with an  STOL
      Flags16	recip_stol:1;	///< bit 15 = this runway s reciprocal end is Short Take Off and Landing and will have no threshold marking and will be marked with an  STOL
   };

   struct RWY_SURFACE_LIGHTS
   {
      Flags8	edge_lights:2;		///< bits 0-1 = are for edge lighting (0 = None, 1 = Low intensity, 2 = Medium intensity, 3 = High intensity)
      Flags8	center_lights:2; 	///< bits 2-3 = are for center line lighting (0 = None, 1= Low intensity, 2 = Medium intensity, 3 = High intensity)
      Flags8	last_red:1;		///< bit 4 = if the last 3000 feet is red
      Flags8	free:3;			///< bits 5-7 = are unused and should be 0
   };

   struct RWY_IDENTIFIERS
   {
      Flags8	number:6;	///< bits 0-5 = are the runway base number 0-36 (both 0 and 36 are 36)
      Flags8	ident:2;	///< bits 6-7 = indent of this runway base (0 = None, 1 = Left, 2= Right, 3 = Center)
   };

   enum RWY_SURFACE_TYPE
      {
      Dirt = 0,
      Concrete,
      Asphalt,
      Grass,
      Coral,
      Gravel,
      OilTreated,
      SteelMats,
      Snow
      };

   enum ROAD_TYPE
      {
      ROAD_TEXTURE_CURRENT = 1,
      ROAD_TEXTURE_STYLE1,
      ROAD_TEXTURE_STYLE2,
      ROAD_TEXTURE_RAILROAD,
      ROAD_TEXTURE_RIVER
      };

   /** Light types.
    * These types are used in the LIGHT command (0xB2).
    */
   enum LIGHT_TYPE
      {
      LIGHT_STROBE    = 6,
      LIGHT_BEACON    = 0,
      LIGHT_NAV	      = 4,
      LIGHT_LANDING   = 5,
      LIGHT_TAXI      = 3,
      LIGHT_LANDING_0 = 9,
      LIGHT_TAXI_0    = 10,
      LIGHT_LANDING_1 = 11,
      LIGHT_TAXI_1    = 12
      };

   enum opcodes
      {
      BGL_EOF = 0x00,
      BGL_NOOP = 0x02,
      BGL_CASE = 0x03,
      BGL_RESERVED = 0x04,
      BGL_SURFACE = 0x05,
      BGL_SPNT = 0x06,
      BGL_CPNT = 0x07,
      BGL_CLOSURE = 0x08,
      BGL_JUMP = 0x0D,
      BGL_DEFRES = 0x0E,
      BGL_STRRES = 0x0F,
      BGL_CNTRES = 0x10,
      BGL_SCOLOR = 0x14,
      BGL_ELEVATION_MAP = 0x15,
      BGL_TEXTURE_ENABLE = 0x17,
      BGL_TEXTURE = 0x18,
      BGL_PALETTE = 0x19,
      BGL_RESLIST = 0x1A,
      BGL_IFIN_BOX_RAW_PLANE = 0x1B,
      BGL_IFIN2 = 0x1C,
      BGL_FACE = 0x1D,
      BGL_HAZE = 0x1E,
      BGL_FACET_TMAP = 0x20,
      BGL_IFIN3 = 0x21,
      BGL_RETURN = 0x22,
      BGL_CALL = 0x23,
      BGL_IFIN1 = 0x24,
      BGL_SEPARATION_PLANE = 0x25,
      BGL_SETWRD = 0x26,
      BGL_GRESLIST = 0x29,
      BGL_GFACET = 0x2A,
      BGL_ADDOBJ32 = 0x2B,
      BGL_REJECT = 0x2C,
      BGL_SCOLOR24 = 0x2D,
      BGL_LCOLOR24 = 0x2E,
      BGL_SCALE = 0x2F,
      BGL_RESROW = 0x31,
      BGL_ADDOBJ = 0x32,
      BGL_INSTANCE = 0x33,
      BGL_SUPER_SCALE = 0x34,
      BGL_PNTROW = 0x35,
      BGL_POINT = 0x37,
      BGL_CONCAVE = 0x38,
      BGL_IFMSK = 0x39,
      BGL_VPOSITION = 0x3A,
      BGL_VINSTANCE = 0x3B,
      BGL_POSITION = 0x3C,
      BGL_SEED = 0x3D,
      BGL_FACET = 0x3E,
      BGL_SHADOW_CALL = 0x3F,
      BGL_SHADOW_VPOSITION = 0x40,
      BGL_SHADOW_VICALL = 0x41,
      BGL_POLYGON_RUNWAY = 0x42,
      BGL_TEXTURE2 = 0x43,
      BGL_TEXTURE_RUNWAY = 0x44,
      BGL_POINT_VICALL = 0x46,
      BGL_Var_SEG = 0x48,
      BGL_BUILDING = 0x49,
      BGL_VSCALE = 0x4C,
      BGL_MOVE_L2G = 0x4D,
      BGL_MOVE_G2L = 0x4E,
      BGL_MOVEWORD = 0x4F,
      BGL_GCOLOR = 0x50,
      BGL_NEW_LCOLOR = 0x51,
      BGL_NEW_SCOLOR = 0x52,
      BGL_SURFACE_TYPE = 0x55,
      BGL_SET_WEATHER = 0x56,
      BGL_WEATHER = 0x57,
      BGL_TEXTURE_BOUNDS = 0x58,
      BGL_TEXTURE_REPEAT = 0x5D,
      BGL_IFSIZEV = 0x5F,
      BGL_FACE_TMAP = 0x60,
      BGL_IFVIS = 0x62,
      BGL_LIBRARY_CALL = 0x63,
      BGL_LIST = 0x64,
      BGL_VSCOLOR = 0x65,
      BGL_VGCOLOR = 0x66,
      BGL_VLCOLOR = 0x67,
      BGL_ROAD_START = 0x69,
      BGL_ROAD_CONT = 0x6A,
      BGL_RIVER_START = 0x6B,
      BGL_RIVER_CONT = 0x6C,
      BGL_IFSIZEH = 0x6D,
      BGL_TAXIWAY_START = 0x6E,
      BGL_TAXIWAY_CONT = 0x6F,
      BGL_AREA_SENSE = 0x70,
      BGL_ALTITUDE_SET = 0x71,
      BGL_IFINBOXP = 0x73,
      BGL_ADDCAT = 0x74,
      BGL_ADDMNT = 0x75,
      BGL_BGL = 0x76,
      BGL_SCALE_AGL = 0x77,
      BGL_ROAD_CONTW = 0x78,
      BGL_RIVER_CONTW = 0x79,
      BGL_GFACET_TMAP = 0x7A,
      BGL_SELECT = 0x7C,
      BGL_PERSPECTIVE = 0x7D,
      BGL_SETWRD_GLOBAL = 0x7E,
      BGL_RESPNT = 0x80,
      BGL_RESCALE = 0x83,
      BGL_FIXED_COLORS = 0x87,
      BGL_JUMP32 = 0x88,
      BGL_Var_BASE32 = 0x89,
      BGL_CALL32 = 0x8A,
      BGL_ADDCAT32 = 0x8B,
      BGL_VFILE_MARKER = 0x8E,
      BGL_ALPHA = 0x8F,
      BGL_TEXT = 0x91,
      BGL_CRASH = 0x94,
      BGL_CRASH_INDIRECT = 0x95,
      BGL_CRASH_START = 0x96,
      BGL_CRASH_SPHERE = 0x97,
      BGL_CRASH_BOX = 0x98,
      BGL_SET_CRASH = 0x99,
      BGL_INTERPOLATE = 0x9E,
      BGL_OVERRIDE = 0x9F,
      BGL_OBJECT = 0xA0,
      BGL_VALPHA = 0xA4,
      BGL_SPRITE_VICALL = 0xA7,
      BGL_TEXTURE_ROAD_START = 0xA8,
      BGL_IFIN_INSTANCED_BOX_PLANE = 0xA9,
      BGL_NEW_RUNWAY = 0xAA,
      BGL_ZBIAS = 0xAC,
      BGL_ANIMATE = 0xAD,
      BGL_TRANSFORM_END = 0xAE,
      BGL_TRANSFORM_MATRIX = 0xAF,
      BGL_LIGHT = 0xB2,
      BGL_IFINF1 = 0xB3,
      BGL_TEXTURE_SIZE = 0xB4,
      BGL_VERTEX_LIST = 0xB5,
      BGL_MATERIAL_LIST = 0xB6,
      BGL_TEXTURE_LIST = 0xB7,
      BGL_SET_MATERIAL = 0xB8,
      BGL_DRAW_TRIAnglE_LIST = 0xB9,
      BGL_DRAW_LINE_LIST = 0xBA,
      BGL_DRAW_POINT_LIST = 0xBB,
      BGL_MOUSERECT_LIST = 0xBF,
      BGL_TAG = 0xB1,
      BGL_SET_MOUSERECT = 0xC0,
      BGL_BEGIN = 0xBC,
      BGL_END = 0xBD
      };

   enum rwy_opcodes
      {
      BGL_RWY_RUNWAY_BASE = 0x01,
      BGL_RWY_BASE_THRESHOLD = 0x02,
      BGL_RWY_RECIP_THRESHOLD = 0x03,
      BGL_RWY_BASE_BLAST_PAD  = 0x04,
      BGL_RWY_RECIP_BLAST_PAD = 0x05,
      BGL_RWY_BASE_APPROACH_LIGHTS = 0x06,
      BGL_RWY_RECIP_APPROACH_LIGHTS = 0x07,
      BGL_RWY_BASE_OVERRUN = 0x08,
      BGL_RWY_RECIP_OVERRUN = 0x09,
      BGL_RWY_BASE_DISTANCE_LEFT = 0x0A,
      BGL_RWY_RECIP_DISTANCE_LEFT = 0x0B
      };

   struct OPCODE {
      unsigned short opcode;
      const char    *name;
      int            size;   /* size includes opcode (2 bytes)
                                -1 indicates that special treatment is needed
                                to find the size */
   };

   static const OPCODE OPCODE_INFO[] =
      {
      { 0x00, "BGL_EOF"              , 2  },
      { 0x01, "OBSOLETE 0x01"        , 2  },
      { 0x02, "BGL_NOOP"             , 2  },
      { 0x03, "BGL_CASE"             , -1 },
      { 0x04, "RESERVED 0x04"        , 2  },
      { 0x05, "BGL_SURFACE"          , 2  },
      { 0x06, "BGL_SPNT"             , 8  },
      { 0x07, "BGL_CPNT"             , 8  },
      { 0x08, "BLG_CLOSURE"          , 2  },
      { 0x09, "OBSOLETE 0x09"        , 2  },
      { 0x0a, "OBSOLETE 0x0a"        , 10 },
      { 0x0b, "OBSOLETE 0x0b"        , 10 },
      { 0x0c, "OBSOLETE 0x0c"        , 2  },
      { 0x0d, "BGL_JUMP"             , 4  },
      { 0x0e, "BGL_DEFRES"           , 8  },
      { 0x0f, "BGL_STRRES"           , 4  },
      { 0x10, "BGL_CNTRES"           , 4  },
      { 0x11, "OBSOLETE 0x11"        , 10 },
      { 0x12, "OBSOLETE 0x12"        , 4  },
      { 0x13, "OBSOLETE 0x13"        , 4  },
      { 0x14, "BGL_SCOLOR"           , 4  },
      { 0x15, "BGL_ELEVATION_MAP"    , -1 },
      { 0x16, "RESERVED 0x16"        , -1 },
      { 0x17, "BGL_TEXTURE_ENABLE"   , 4  },
      { 0x18, "BGL_TEXTURE"          , 24 },
      { 0x19, "BGL_PALETTE"          , 16 },
      { 0x1a, "BGL_RESLIST"          , -1 },
      { 0x1b, "BGL_IFIN_BOX_RAW_PLANE", 22 },
      { 0x1c, "BGL_IFIN2"            , 16 },
      { 0x1d, "BGL_FACE"             , -1 },
      { 0x1e, "BGL_HAZE"             , 4  },
      { 0x1f, "RESERVED 0x1f"        , 4  },
      { 0x20, "BGL_FACET_TMAP"       , -1 },
      { 0x21, "BGL_IFIN3"            , 22 },
      { 0x22, "BGL_RETURN"           , 2  },
      { 0x23, "BGL_CALL"             , 4  },
      { 0x24, "BGL_IFIN1"            , 10 },
      { 0x25, "BGL_SEPARATION_PLANE" , 14 },
      { 0x26, "BGL_SETWRD"           , 6  },
      { 0x27, "OBSOLETE 0x27"        , -1 },
      { 0x28, "OBSOLETE 0x28"        , 10 },
      { 0x29, "BGL_GRESLIST"         , -1 },
      { 0x2a, "BGL_GFACET"           , -1 },
      { 0x2b, "BGL_ADDOBJ32"         , 6  },
      { 0x2c, "BGL_REJECT"           , 12 },
      { 0x2d, "BGL_SCOLOR24"         , 6  },
      { 0x2e, "BGL_LCOLOR24"         , 6  },
      { 0x2f, "BGL_SCALE"            , 32 },
      { 0x30, "OBSOLETE 0x30"        , 4  },
      { 0x31, "BGL_RESROW"           , 18 },
      { 0x32, "BGL_ADDOBJ"           , 4  },
      { 0x33, "BGL_INSTANCE"         , 10 },
      { 0x34, "BGL_SUPER_SCALE"      , 10 },
      { 0x35, "BGL_PNTROW"           , 16 },
      { 0x36, "OBSOLETE 0x36"        , -1 },
      { 0x37, "BGL_POINT"            , 8  },
      { 0x38, "BGL_CONCAVE"          , 2  },
      { 0x39, "BGL_IFMSK"            , 8  },
      { 0x3a, "BGL_VPOSITION"        , 12 },
      { 0x3b, "BGL_VINSTANCE"        , 6  },
      { 0x3c, "BGL_POSITION"         , 28 },
      { 0x3d, "BGL_SEED"             , 24 },
      { 0x3e, "BGL_FACET"            , -1 },
      { 0x3f, "BGL_SHADOW_CALL"      , 4  },
      { 0x40, "BGL_SHADOW_VPOSITION" , 12 },
      { 0x41, "BGL_SHADOW_VICALL"    , 6  },
      { 0x42, "BGL_POLYGON_RUNWAY"   , 40 },
      { 0x43, "BGL_TEXTURE2"         , -1 },
      { 0x44, "BGL_TEXTURE_RUNWAY"   , 40 },
      { 0x45, "OBSOLETE 0x45"        , 16 },
      { 0x46, "BGL_POINT_VICALL"     , 22 },
      { 0x47, "RESERVED"             , 4  },
      { 0x48, "BGL_Var_SEG"          , 4  },
      { 0x49, "BGL_BUILDING"         , 18 },
      { 0x4a, "OBSOLETE 0x4A"        , 22 },
      { 0x4b, "OBSOLETE 0x4B"        , -1 },
      { 0x4c, "BGL_VSCALE"           , 16 },
      { 0x4d, "BGL_MOVEL2G"          , 6  },
      { 0x4e, "BGL_MOVEG2L"          , 6  },
      { 0x4f, "BGL_MOVEWORD"         , 6  },
      { 0x50, "BGL_GCOLOR"           , 4  },
      { 0x51, "BGL_NEW_LCOLOR"       , 4  },
      { 0x52, "BGL_NEW_SCOLOR"       , 4  },
      { 0x53, "OBSOLETE 0x53"        , 4  },
      { 0x54, "OBSOLETE 0x54"        , 6  },
      { 0x55, "BGL_SURFACE_TYPE"     , 10 },
      { 0x56, "BGL_SET_WEATHER"      , 4  },
      { 0x57, "BGL_SET_WEATHER"      , 10 },
      { 0x58, "BGL_TEXTURE_BOUNDS"   , 10 },
      { 0x59, "OBSOLETE 0x59"        , 4  },
      { 0x5a, "OBSOLETE 0x5a"        , 4  },
      { 0x5b, "OBSOLETE 0x5b"        , 4  },
      { 0x5c, "OBSOLETE 0x5c"        , 6  },
      { 0x5d, "BGL_TEXTURE_REPEAT"   , 8  },
      { 0x5e, "OBSOLETE 0x5e"        , 4  },
      { 0x5f, "BGL_IFSIZEV"          , 8  },
      { 0x60, "BGL_FACE_TMAP"        , -1 },
      { 0x61, "RESERVED 0x53"        , 6  },
      { 0x62, "BGL_IFVIS"            , -1 },
      { 0x63, "BGL_LIBRARY_CALL"     , 20 },
      { 0x64, "BGL_LIST"             , -1 },
      { 0x65, "BGL_VSCOLOR"          , 4  },
      { 0x66, "BGL_VGCOLOR"          , 4  },
      { 0x67, "BGL_VLCOLOR"          , 4  },
      { 0x68, "OBSOLETE"             , 8  },
      { 0x69, "BGL_ROAD_START"       , 10 },
      { 0x6a, "BGL_ROAD_CONT"        , 8  },
      { 0x6b, "BGL_RIVER_START"      , 10 },
      { 0x6c, "BGL_RIVER_CONT"       , 8  },
      { 0x6d, "BGL_IFSIZEH"          , 8  },
      { 0x6e, "BGL_TAXIWAY_START"    , 10 },
      { 0x6f, "BGL_TAXIWAY_CONT"     , 8  },
      { 0x70, "BGL_AREA_SENSE"       , -1 },
      { 0x71, "BGL_ALTITUDE_SET"     , 4  },
      { 0x72, "OBSOLETE 0x72"        , 20 },
      { 0x73, "BGL_IFINBOXP"         , 16 },
      { 0x74, "BGL_ADDCAT"           , 6  },
      { 0x75, "BGL_ADDMNT"           , 4  },
      { 0x76, "BGL_BGL"              , 2  },
      { 0x77, "BGL_SCALE_AGL"        , 32 },
      { 0x78, "BGL_ROAD_CONTW"       , 10 },
      { 0x79, "BGL_RIVER_CONTW"      , 10 },
      { 0x7a, "BGL_GFACET_TMAP"      , -1 },
      { 0x7b, "OBSOLETE 0x7b"        , -1 },
      { 0x7c, "BGL_SELECT"           , 10 },
      { 0x7d, "BGL_PERSPECTIVE"      , 2  },
      { 0x7e, "BGL_SETWRD_GLOBAL"    , 6  },
      { 0x7f, "OBSOLETE 0x7f"        , 2  },
      { 0x80, "BGL_RESPNT"           , 4  },
      { 0x81, "OBSOLETE 0x81"        , 4  },
      { 0x82, "OBSOLETE 0x82"        , 28 },
      { 0x83, "BGL_RESCALE"          , 32 },
      { 0x84, "OBSOLETE 0x84"        , 8  },
      { 0x85, "OBSOLETE 0x85"        , 2  },
      { 0x86, "OBSOLETE 0x86"        , 3  },
      { 0x87, "BGL_FIXED_COLORS"     , 4  },
      { 0x88, "BGL_JUMP32"           , 6  },
      { 0x89, "BGL_Var_BASE32"       , 6  },
      { 0x8a, "BGL_CALL32"           , 6  },
      { 0x8b, "BGL_ADDCAT32"         , 8  },
      { 0x8c, "RESERVED 0x8c"        , 6  },
      { 0x8d, "RESERVED 0x8d"        , 6  },
      { 0x8e, "BGL_VFILE_MARKER"     , 4  },
      { 0x8f, "BGL_ALPHA"            , 6  },
      { 0x90, "RESERVED 0x90"        , -1 },
      { 0x91, "BGL_TEXT"             , 12 },
      { 0x92, "OBSOLETE 0x92"        , 4  },
      { 0x93, "RESERVED 0x93"        , 4  },
      { 0x94, "BGL_CRASH"            , 12 },
      { 0x95, "BGL_CRASH_INDIRECT"   , 10 },
      { 0x96, "BGL_CRASH_START"      , 6  },
      { 0x97, "BGL_CRASH_SPHERE"     , 6  },
      { 0x98, "BGL_CRASH_BOX"        , 22 },
      { 0x99, "BGL_SET_CRASH"        , 4  },
      { 0x9a, "OBSOLETE 0x9a"        , -1 },
      { 0x9b, "RESERVED 0x9b"        , 8  },
      { 0x9c, "RESERVED 0x9c"        , 6  },
      { 0x9d, "RESERVED 0x9d"        , 14 },
      { 0x9e, "BGL_INTERPOLATE"      , 20 },
      { 0x9f, "BGL_OVERRIDE"         , 6  },
      { 0xa0, "BGL_OBJECT"           , -1 },
      { 0xa1, "OBSOLETE 0xA1"        , 10 },
      { 0xa2, "OBSOLETE 0xA2"        , 8  },
      { 0xa3, "OBSOLETE 0xA3"        , -1 },
      { 0xa4, "BGL_VALPHA"           , 4  },
      { 0xa5, "OBSOLETE 0xA5"        , 4  },
      { 0xa6, "OBSOLETE 0xA6"        , 8  },
      { 0xa7, "BGL_SPRITE_VCALL"     , 22 },
      { 0xa8, "BGL_TEXTURE_ROAD_START", 12},
      { 0xa9, "BGL_IFIN_INSTANCE_BOX_PLANE", 22},
      { 0xaa, "BGL_NEW_RUNWAY"       , -1 },
      { 0xab, "RESERVED 0xAB"        , 38 },
      { 0xac, "BGL_ZBIAS"            , 4  },
      { 0xad, "BGL_ANIMATE"          , 30 },
      { 0xae, "BGL_TRANSFORM_END"    , 2  },
      { 0xaf, "BGL_TRANSFORM_MATRIX" , 50 },
      { 0xb0, "UNKNOWN 0xB0"         , -1 },
      { 0xb1, "BGL_TAG"              , -1 },
      { 0xb2, "BGL_LIGHT"            , 44 },
      { 0xb3, "BGL_IFINF1"           , 14 },
      { 0xb4, "BGL_TEXTURE_SIZE"     ,  6 },
      { 0xb5, "BGL_VERTEX_LIST"      , -1 },
      { 0xb6, "BGL_MATERIAL_LIST"    , -1 },
      { 0xb7, "BGL_TEXTURE_LIST"     , -1 },
      { 0xb8, "BGL_SET_MATERIAL"     ,  6 },
      { 0xb9, "BGL_DRAW_TRIAnglE_LIST", -1 },
      { 0xba, "BGL_DRAW_LINE_LIST"   , -1 },
      { 0xbb, "BGL_DRAW_POINT_LIST"  , -1 },
      { 0xbc, "BGL_BEGIN"            ,  6 },
      { 0xbd, "BGL_END"              ,  2 },
      { 0xbe, "UNKNOWN 0xBE"         , -1 },
      { 0xbf, "BGL_MOUSERECT_LIST"   , -1 },
      { 0xc0, "BGL_SET_MOUSERECT"    , -1 },
      { 0xc1, "UNKNOWN 0xC1"         , -1 },
      { 0xc2, "UNKNOWN 0xC2"         , -1 },
      { 0xc3, "UNKNOWN 0xC3"         , -1 },
      { 0xc4, "UNKNOWN 0xC4"         , -1 },
      { 0xc5, "UNKNOWN 0xC5"         , -1 },
      { 0xc6, "UNKNOWN 0xC6"         , -1 },
      { 0xc7, "UNKNOWN 0xC7"         , -1 },
      { 0xc8, "UNKNOWN 0xC8"         , -1 },
      { 0xc9, "UNKNOWN 0xC9"         , -1 },
      { 0xca, "UNKNOWN 0xCA"         , -1 },
      { 0xcb, "UNKNOWN 0xCB"         , -1 },
      { 0xcc, "UNKNOWN 0xCC"         , -1 },
      { 0xcd, "UNKNOWN 0xCD"         , -1 },
      { 0xce, "UNKNOWN 0xCE"         , -1 },
      { 0xcf, "UNKNOWN 0xCF"         , -1 },
      { 0xd0, "UNKNOWN 0xD0"         , -1 },
      { 0xd1, "UNKNOWN 0xD1"         , -1 },
      { 0xd2, "UNKNOWN 0xD2"         , -1 },
      { 0xd3, "UNKNOWN 0xD3"         , -1 },
      { 0xd4, "UNKNOWN 0xD4"         , -1 },
      { 0xd5, "UNKNOWN 0xD5"         , -1 },
      { 0xd6, "UNKNOWN 0xD6"         , -1 },
      { 0xd7, "UNKNOWN 0xD7"         , -1 },
      { 0xd8, "UNKNOWN 0xD8"         , -1 },
      { 0xd9, "UNKNOWN 0xD9"         , -1 },
      { 0xda, "UNKNOWN 0xDA"         , -1 },
      { 0xdb, "UNKNOWN 0xDB"         , -1 },
      { 0xdc, "UNKNOWN 0xDC"         , -1 },
      { 0xdd, "UNKNOWN 0xDD"         , -1 },
      { 0xde, "UNKNOWN 0xDE"         , -1 },
      { 0xdf, "UNKNOWN 0xDF"         , -1 },
      { 0xe0, "UNKNOWN 0xE0"         , -1 },
      { 0xe1, "UNKNOWN 0xE1"         , -1 },
      { 0xe2, "UNKNOWN 0xE2"         , -1 },
      { 0xe3, "UNKNOWN 0xE3"         , -1 },
      { 0xe4, "UNKNOWN 0xE4"         , -1 },
      { 0xe5, "UNKNOWN 0xE5"         , -1 },
      { 0xe6, "UNKNOWN 0xE6"         , -1 },
      { 0xe7, "UNKNOWN 0xE7"         , -1 },
      { 0xe8, "UNKNOWN 0xE8"         , -1 },
      { 0xe9, "UNKNOWN 0xE9"         , -1 },
      { 0xea, "UNKNOWN 0xEA"         , -1 },
      { 0xeb, "UNKNOWN 0xEB"         , -1 },
      { 0xec, "UNKNOWN 0xEC"         , -1 },
      { 0xed, "UNKNOWN 0xED"         , -1 },
      { 0xee, "UNKNOWN 0xEE"         , -1 },
      { 0xef, "UNKNOWN 0xEF"         , -1 },
      { 0xf0, "UNKNOWN 0xF0"         , -1 },
      { 0xf1, "UNKNOWN 0xF1"         , -1 },
      { 0xf2, "UNKNOWN 0xF2"         , -1 },
      { 0xf3, "UNKNOWN 0xF3"         , -1 },
      { 0xf4, "UNKNOWN 0xF4"         , -1 },
      { 0xf5, "UNKNOWN 0xF5"         , -1 },
      { 0xf6, "UNKNOWN 0xF6"         , -1 },
      { 0xf7, "UNKNOWN 0xF7"         , -1 },
      { 0xf8, "UNKNOWN 0xF8"         , -1 },
      { 0xf9, "UNKNOWN 0xF9"         , -1 },
      { 0xfa, "UNKNOWN 0xFA"         , -1 },
      { 0xfb, "UNKNOWN 0xFB"         , -1 },
      { 0xfc, "UNKNOWN 0xFC"         , -1 },
      { 0xfd, "UNKNOWN 0xFD"         , -1 },
      { 0xfe, "UNKNOWN 0xFE"         , -1 },
      { 0xff, "UNKNOWN 0xFF"         , -1 }
      };

   // MSFS Earth model
   static const double EQ_CIRCUM    = 40075000.0;
   static const double EQ_DIAM      = 12756270.0;
   static const double POLAR_CIRCUM = 40007000.0;
   static const double POLAR_DIAM   = 12734620.0;

   static const UNICOL UNICOL_PALETTE_1[] =
      {
      {  24,  24,  24, 255 },
      {  56,  56,  56, 255 },
      { 121, 121, 121, 255 },
      { 203, 203, 203, 255 },
      { 255, 255, 255, 255 },
      { 252,  60,  60, 255 },
      {  60, 252,  60, 255 },
      {   0, 153, 230, 255 },
      { 252, 126,   0, 255 },
      { 252, 252,   0, 255 },
      { 125, 105,  80, 255 },
      { 225, 189, 144, 255 },
      { 252,  99,  63, 255 },
      { 153, 198,  81, 255 },
      {   0,  58, 104, 255 },
      { 255,   0,   0, 255 },
      {  64, 255,  64, 255 },
      {   0,   0, 192, 255 },
      {   0, 105, 105, 255 },
      { 255, 128,   0, 255 },
      { 255, 255,   0, 255 },
      { 228, 228, 228, 255 },
      { 228, 228, 228, 255 },
      {  84,  20,  20, 255 },
      {  20,  84,  20, 255 },
      {   0,  40,  84, 255 },
      {  84,  42,   0, 255 },
      {  84,  84,   0, 255 },
      {  75,  63,  48, 255 },
      {  75,  63,  48, 255 },
      {  84,  33,  21, 255 },
      {  51,  66,  27, 255 },
      { 126,  30,  30, 255 },
      {  30, 126,  30, 255 },
      {   0,  71, 122, 255 },
      { 112,  56,   0, 255 },
      { 112, 112,   0, 255 },
      {  75,  63,  48, 255 },
      { 100,  84,  64, 255 },
      { 112,  44,  28, 255 },
      {  68,  88,  36, 255 },
      { 189,  45,  45, 255 },
      {  45, 189,  45, 255 },
      {   0, 112, 179, 255 },
      { 168,  84,   0, 255 },
      { 168, 168,   0, 255 },
      { 100,  84,  64, 255 },
      { 150, 126,  96, 255 },
      { 168,  66,  42, 255 },
      { 102, 132,  54, 255 },
      {  82,  82,  82, 255 },
      { 163, 163, 163, 255 },
      { 196, 196, 196, 255 }
      };

   //===========================================================================
   // Alternative palette for transparent colors (?)
   // (same as in fs5.pal?)

   static const UNICOL UNICOL_PALETTE_2[] =
      {
      { 0, 0, 0, 40 },
      { 8, 8, 8, 40 },
      { 16, 16, 16, 40 },
      { 24, 24, 24, 40 },
      { 32, 32, 32, 40 },
      { 40, 40, 40, 40 },
      { 48, 48, 48, 40 },
      { 56, 56, 56, 40 },
      { 65, 65, 65, 40 },
      { 73, 73, 73, 40 },
      { 81, 81, 81, 40 },
      { 89, 89, 89, 40 },
      { 97, 97, 97, 40 },
      { 105, 105, 105, 40 },
      { 113, 113, 113, 40 },
      { 121, 121, 121, 40 },
      { 130, 130, 130, 40 },
      { 138, 138, 138, 40 },
      { 146, 146, 146, 40 },
      { 154, 154, 154, 40 },
      { 162, 162, 162, 40 },
      { 170, 170, 170, 40 },
      { 178, 178, 178, 40 },
      { 186, 186, 186, 40 },
      { 195, 195, 195, 40 },
      { 203, 203, 203, 40 },
      { 211, 211, 211, 40 },
      { 219, 219, 219, 40 },
      { 227, 227, 227, 40 },
      { 235, 235, 235, 40 },
      { 247, 247, 247, 40 },
      { 255, 255, 255, 40 },
      { 21, 5, 5, 40 },
      { 42, 10, 10, 40 },
      { 63, 15, 15, 40 },
      { 84, 20, 20, 40 },
      { 105, 25, 25, 40 },
      { 126, 30, 30, 40 },
      { 147, 35, 35, 40 },
      { 168, 40, 40, 40 },
      { 189, 45, 45, 40 },
      { 210, 50, 50, 40 },
      { 231, 55, 55, 40 },
      { 252, 60, 60, 40 },
      { 5, 21, 5, 40 },
      { 10, 42, 10, 40 },
      { 15, 63, 15, 40 },
      { 20, 84, 20, 40 },
      { 25, 105, 25, 40 },
      { 30, 126, 30, 40 },
      { 35, 147, 35, 40 },
      { 40, 168, 40, 40 },
      { 45, 189, 45, 40 },
      { 50, 210, 50, 40 },
      { 55, 231, 55, 40 },
      { 60, 252, 60, 40 },
      { 0, 7, 23, 40 },
      { 0, 15, 40, 40 },
      { 0, 23, 58, 40 },
      { 0, 40, 84, 40 },
      { 0, 64, 104, 40 },
      { 0, 71, 122, 40 },
      { 0, 87, 143, 40 },
      { 0, 99, 156, 40 },
      { 0, 112, 179, 40 },
      { 0, 128, 199, 40 },
      { 0, 143, 215, 40 },
      { 0, 153, 230, 40 },
      { 28, 14, 0, 40 },
      { 56, 28, 0, 40 },
      { 84, 42, 0, 40 },
      { 112, 56, 0, 40 },
      { 140, 70, 0, 40 },
      { 168, 84, 0, 40 },
      { 196, 98, 0, 40 },
      { 224, 112, 0, 40 },
      { 252, 126, 0, 40 },
      { 28, 28, 0, 40 },
      { 56, 56, 0, 40 },
      { 84, 84, 0, 40 },
      { 112, 112, 0, 40 },
      { 140, 140, 0, 40 },
      { 168, 168, 0, 40 },
      { 196, 196, 0, 40 },
      { 224, 224, 0, 40 },
      { 252, 252, 0, 40 },
      { 25, 21, 16, 40 },
      { 50, 42, 32, 40 },
      { 75, 63, 48, 40 },
      { 100, 84, 64, 40 },
      { 125, 105, 80, 40 },
      { 150, 126, 96, 40 },
      { 175, 147, 112, 40 },
      { 200, 168, 128, 40 },
      { 225, 189, 144, 40 },
      { 28, 11, 7, 40 },
      { 56, 22, 14, 40 },
      { 84, 33, 21, 40 },
      { 112, 44, 28, 40 },
      { 140, 55, 35, 40 },
      { 168, 66, 42, 40 },
      { 196, 77, 49, 40 },
      { 224, 88, 56, 40 },
      { 252, 99, 63, 40 },
      { 17, 22, 9, 40 },
      { 34, 44, 18, 40 },
      { 51, 66, 27, 40 },
      { 68, 88, 36, 40 },
      { 85, 110, 45, 40 },
      { 102, 132, 54, 40 },
      { 119, 154, 63, 40 },
      { 136, 176, 72, 40 },
      { 153, 198, 81, 40 }
      };

   inline double cvtLat(SInt32 lat)
      {
      return 360.0*(double)lat/POLAR_CIRCUM;
      }

   inline double cvtLon(Angl32 lon)
      {
      return 360.0*(double)lon/0xffffffff;
      }

   /// Convert SIF48 to double (meters)
   inline double cvtSIF48(SIF48 val)
      {
      /*
      int v = (val.i << 16) | val.f;
      unsigned long long int d = 0xffffffff;
      d <<= 32;
      d |= 0xffff;
      return (double)v/d;
      */
      return (double)val.i + (double)val.f/0xffff;
      }

   /// Convert SIF48 to double (degrees)
   inline double cvtSIF48Deg(SIF48 val)
      {
      return 360.0*((double)val.i + (double)val.f/0xffff)/POLAR_CIRCUM;
      }

   inline double cvtAngl48(Angl48 val)
      {
      unsigned long long int v = val.hi;
      v <<= 16;
      v |= val.lo;
      unsigned long long int div = 0xffffffffffffll;
      return 360.0*(double)v/(double)div;
      }


   inline std::ostream& operator << (std::ostream &os, const LLA &lla)
      {
      os << cvtSIF48Deg(lla.lat) << "N "
         << cvtAngl48(lla.lon) << "E, "
         << cvtSIF48(lla.alt) << "m\n";
      return os;
      }

   struct MDLH
   {
      UInt32	reserved1;
      UInt32	reserved2;
      UInt32	size_radius;
      UInt32	reserved3;
      UInt32	reserved4;
      UInt32	params_length;
      char	product_code[4];
      UInt32	build_number;
   };

   struct GUid
   {
      UInt8 g1[4];
      UInt8 g2[2];
      UInt8 g3[2];
      UInt8 g4[2];
      UInt8 g5[6];
   };

   struct DICT_PARAM
   {
      UInt32	uType;
      UInt32	uOffset;
      UInt32	uLen;
      GUid      guidParam;
   };

   enum STD_PARAMS_OFFSET
      {
      PARTS_VISIBLE 		= 0x90,
      BOMB_ROCKET_VISIBLE	= 0x8e,
      PROP_VISIBLE		= 0x8c,
      STROBE			= 0x8a,
      LIGHTS			= 0x88,
      RIGHT_GEAR_B		= 0x86,
      RIGHT_GEAR_P		= 0x84,
      LEFT_GEAR_B		= 0x82,
      LEFT_GEAR_P		= 0x80,
      FRONT_GEAR_P		= 0x7e,
      PROP_POS			= 0x7c,
      ENGINE_RPM		= 0x7a,
      RUDDER			= 0x78,
      ELEVATOR			= 0x76,
      RIGHT_FLAP		= 0x74,
      LEFT_FLAP			= 0x72,
      RIGHT_AILERON		= 0x70,
      LEFT_AILERON              = 0x6e,
      GEAR_SMOKE                = 0x6c,
      GEN_MODEL			= 0x68
      };

   enum GEN_MODEL
      {
      GEN_MODEL_INSIDE   = 0x0001,
      GEN_MODEL_OUTSIDE  = 0x0002,
      GEN_MODEL_DOWNWARD = 0x0008,
      GEN_MODEL_FRONT    = 0x0010,
      GEN_MODEL_REAR     = 0x0020,
      GEN_MODEL_NOSHADOW = 0x1000,
      GEN_MODEL_DISPLAY  = 0x8000,
      };

   enum PARTS_VISIBLE
      {
      VISIBLE_RIGHTWING	= 0x0001,
      VISIBLE_LEFTWING	= 0x0002,
      VISIBLE_TAIL      = 0x0004,
      };

   enum GenType
      {
      Float32_TYPE = 1,
      UInt32_TYPE = 2,
      STRING_TYPE = 3,
      UInt16_TYPE = 4,
      GUid_TYPE = 5,
      Flags16_TYPE = 6
      };

   enum ParamName
      {
      parts_visible = 0,
      bomb_rocket_visible,
      prop_visible,
      strobe,
      lights,
      right_gear_b,
      right_gear_p,
      left_gear_b,
      left_gear_p,
      front_gear_p,
      prop_pos,
      engine_rpm,
      rudder,
      elevator,
      right_flap,
      left_flap,
      right_aileron,
      left_aileron,
      gear_smoke,
      gen_model,
      l_gear,
      r_gear,
      c_gear,
      r_spoiler,
      l_spoiler,
      r_thrust_rev,
      l_thrust_rev,
      nnumber,
      color_nnumber,
      font_nnumber,
      visor,
      concorde_nose,
      engine0,
      engine1,
      engine2,
      engine3,
      prop_pos0,
      prop_pos1,
      prop_rpm0,
      prop_rpm1,
      trimtab_elevator,
      trimtab_l_aileron,
      trimtab_r_aileron,
      trimtab_rudder,
      rudder_water_rotate,
      elevon0L,
      elevon1L,
      elevon2L,
      elevon3R,
      elevon4R,
      elevon5R,
      c_wheel,
      g_lightStates,
      crash_check,
      l_wingfold,
      r_wingfold,
      l_pontoon,
      r_pontoon,
      cowling,
      f_canopy,
      r_canopy,
      vc_f_canopy,
      vc_r_canopy,
      Door_Passenger,
      Door_Cargo,
      pilot,
      gunner0,
      gunner1,
      gunner2,
      tailhook,
      l_flap_key,
      r_flap_key,
      userdefined0,
      userdefined1,
      userdefined2,
      userdefined3,
      userdefined4,
      userdefined5,
      userdefined6,
      userdefined7,
      userdefined8,
      rudder_water_deploy,
      mount0,
      mount1,
      mount2,
      mount3,
      mount4,
      mount5,
      mount6,
      mount7,
      mount8,
      mount9,
      mount10,
      bomb_bay,
      endcaps1,
      endcaps2,
      c_tire,
      l_tire,
      r_tire,
      gun0,
      gun1,
      gun2,
      gun3,
      gun4,
      gun5,
      gun6,
      gun7,
      gun8,
      gun9,
      gun10,
      gun11,
      gun12,
      gun13,
      gun14,
      gun15,
      barrel0,
      barrel1,
      barrel2,
      barrel3,
      barrel4,
      barrel5,
      barrel6,
      barrel7,
      barrel8,
      barrel9,
      barrel10,
      barrel11,
      barrel12,
      barrel13,
      barrel14,
      barrel15,
      damaged0,
      bullets0,
      bullets1,
      bullets2,
      bullets3,
      bullets4,
      bullets5,
      bullets6,
      bullets7,
      pylon,
      cockpit_detail,
      battery_switch,
      l_pct_lead_edge_flap0,
      r_pct_lead_edge_flap0,
      l_pct_lead_edge_flap1,
      r_pct_lead_edge_flap1,
      l_pct_trail_edge_flap0,
      r_pct_trail_edge_flap0,
      l_pct_trail_edge_flap1,
      r_pct_trail_edge_flap1,
      thrust_reverser0,
      thrust_reverser1,
      thrust_reverser2,
      thrust_reverser3,
      lever_throttle0,
      lever_throttle1,
      lever_throttle2,
      lever_throttle3,
      lever_prop_pitch0,
      lever_prop_pitch1,
      lever_prop_pitch2,
      lever_prop_pitch3,
      lever_mixture0,
      lever_mixture1,
      lever_mixture2,
      lever_mixture3,
      lever_water_rudder,
      lever_stick_fore_aft,
      lever_stick_l_r,
      lever_pedals_l_r,
      lever_collective,
      lever_landing_gear,
      lever_speed_brake,
      lever_parking_brake,
      lever_flap,
      lever_cowl_flaps0,
      lever_cowl_flaps1,
      lever_cowl_flaps2,
      lever_cowl_flaps3,
      cowl_flaps0,
      cowl_flaps1,
      cowl_flaps2,
      cowl_flaps3,
      aux_gear,
      NUM_PARAMS
      };

   struct ParamValue
   {
      GenType type;
      Float32 float_val;
      UInt32  ulong_val;
      std::string  string_val;
      UInt16  ushort_val;
      std::string param_name;

      ParamValue(GenType t, const std::string& name = "")
         {
         type = t;
         float_val  = 0.0f;
         ulong_val  = 0;
         ushort_val = 0;
         param_name = name;
         }
   };

   struct GUidMap
   {
      ParamName  name;
      char     guid_str[64];
      char     name_str[64];
   };

   static const GUidMap AIRCRAFT_PARAMS[] =
      {
      { l_gear, "2A09AF32-34E5-11D3-A479-00105A24D108", "l_gear" },
      { r_gear, "BA9EBED0-34E5-11D3-A479-00105A24D108", "r_gear" },
      { c_gear, "FC649DE0-34E5-11D3-A479-00105A24D108", "c_gear" },
      { r_spoiler, "DC7E5F6D-33A3-4183-AC11-997A0E14575A", "r_spoiler" },
      { l_spoiler, "E54A2C80-935E-4C5D-8700-1E1E495E0077", "l_spoiler" },
      { r_thrust_rev, "7961D10E-2DC3-426F-8575-ADA21077CCE3", "r_thrust_rev" },
      { l_thrust_rev, "860A6933-8794-4495-88C1-014FFF460EC2", "l_thrust_rev" },
      { nnumber, "7A8F7963-34F1-11D3-A479-00105A24D108", "nnumber" },
      { color_nnumber, "43297401-571B-11D3-B901-00104B36AE4A", "color_nnumber" },
      { font_nnumber, "43297404-571B-11D3-B901-00104B36AE4A", "font_nnumber" },
      { visor, "89E2CA9B-1E3C-4647-B1C2-50117EC99508", "visor" },
      { concorde_nose, "88156FC9-0FB1-4392-901A-311BB154EBFE", "concorde_nose" },
      { engine0, "FBD8EE2C-39A7-4E9C-B527-AA632FE7E50F", "engine0" },
      { engine1, "D50CA991-BE29-49DC-811C-9BAD544D9AD9", "engine1" },
      { engine2, "B50DD089-FD07-45D7-A84F-6BC19F2F5D83", "engine2" },
      { engine3, "53CAB4CC-FE7A-40B3-9EB2-C5805BC949B7", "engine3" },
      { prop_pos0, "325BFD5E-3D37-4038-8329-BFD42780AA0D", "prop_pos0" },
      { prop_pos1, "8CB47539-B8F0-4D7D-9DE1-D227D727D391", "prop_pos1" },
      { prop_rpm0, "EEDA0F04-3CAB-44C8-8AB2-90611C419E3A", "prop_rpm0" },
      { prop_rpm1, "8CB47536-B8F0-4D7D-9DE1-D227D727D391", "prop_rpm1" },
      { trimtab_elevator, "DE76EABD-43D1-11D3-BA66-0000F81F5859", "trimtab_elevator" },
      { trimtab_l_aileron, "2F3FF489-271D-4C6C-9D60-5748BFE73528", "trimtab_l_aileron" },
      { trimtab_r_aileron, "2F3FF48A-271D-4C6C-9D60-5748BFE73528", "trimtab_r_aileron" },
      { trimtab_rudder, "2F3FF48B-271D-4C6C-9D60-5748BFE73528", "trimtab_rudder" },
      { rudder_water_rotate, "2F3FF48C-271D-4C6C-9D60-5748BFE73528", "rudder_water_rotate" },
      { elevon0L, "2044D7D1-42DB-4DE6-BCD6-86F04C600F01", "elevon0L" },
      { elevon1L, "063579E2-A48E-48CC-BC09-BA27D3C28C6D", "elevon1L" },
      { elevon2L, "9C51185B-00FE-41C4-9138-469C94766F98", "elevon2L" },
      { elevon3R, "CA25DFC6-B34E-46E1-83EF-32FD4FC1FA9C", "elevon3R" },
      { elevon4R, "1493480B-472C-4699-841C-E3DA9DAA5657", "elevon4R" },
      { elevon5R, "CB62B757-F9FF-49F5-9174-2A05CBBD74BE", "elevon5R" },
      { c_wheel, "81BDA9A2-383C-4FED-9041-8DB0DF1DAD97", "c_wheel" },
      { g_lightStates, "57F0E99D-0523-4E9C-BCB6-12BB2FE73F06", "g_lightStates" },
      { crash_check, "0EECADB4-1724-41C6-B977-D87A4C9544E8", "crash_check" },
      { l_wingfold, "9462BE35-883E-4E3A-A5DA-278BCD2F7526", "l_wingfold" },
      { r_wingfold, "10423E7D-2C14-419E-AC81-3AC6AD0EDA41", "r_wingfold" },
      { l_pontoon, "9E5C1C8C-D1A9-477F-B78C-68AD64D4AF56", "l_pontoon" },
      { r_pontoon, "9E5C1C8D-D1A9-477F-B78C-68AD64D4AF56", "r_pontoon" },
      { cowling, "9E5C1C8E-D1A9-477F-B78C-68AD64D4AF56", "cowling" },
      { f_canopy, "9E5C1C91-D1A9-477F-B78C-68AD64D4AF56", "f_canopy" },
      { r_canopy, "9E5C1C92-D1A9-477F-B78C-68AD64D4AF56", "r_canopy" },
      { vc_f_canopy, "9E5C1C91-D1A9-477F-B78C-68AD64D4AF56", "vc_f_canopy" },
      { vc_r_canopy, "9E5C1C92-D1A9-477F-B78C-68AD64D4AF56", "vc_r_canopy" },
      { Door_Passenger, "9E5C1C91-D1A9-477F-B78C-68AD64D4AF56", "Door_Passenger" },
      { Door_Cargo, "9E5C1C92-D1A9-477F-B78C-68AD64D4AF56", "Door_Cargo" },
      { pilot, "9E5C1C93-D1A9-477F-B78C-68AD64D4AF56", "pilot" },
      { gunner0, "9E5C1C94-D1A9-477F-B78C-68AD64D4AF56", "gunner0" },
      { gunner1, "9E5C1C95-D1A9-477F-B78C-68AD64D4AF56", "gunner1" },
      { gunner2, "9E5C1C96-D1A9-477F-B78C-68AD64D4AF56", "gunner2" },
      { tailhook, "779F7B58-A315-4EFE-A17C-BC4D5E5D478F", "tailhook" },
      { l_flap_key, "B70D66B7-FD55-4C7A-AFD8-A7A7640DDAA5", "l_flap_key" },
      { r_flap_key, "B70D66B8-FD55-4C7A-AFD8-A7A7640DDAA5", "r_flap_key" },
      { userdefined0, "861C234E-CCDA-4837-970B-EA3C9D27E351", "userdefined0" },
      { userdefined1, "B4D13006-1B70-42F6-B78C-D51722F36991", "userdefined1" },
      { userdefined2, "7E42596D-9B09-4016-9213-A9F68B7910E2", "userdefined2" },
      { userdefined3, "78005967-3006-425D-A411-0C754F45AFCB", "userdefined3" },
      { userdefined4, "69158670-F775-43E7-8EA4-B64241710D6A", "userdefined4" },
      { userdefined5, "5CF16F75-CC31-4DD3-8AD2-7EF647B8C495", "userdefined5" },
      { userdefined6, "E6732DD7-E4D5-47AF-95CF-D48ABEC16F62", "userdefined6" },
      { userdefined7, "98875F9E-E89E-45EC-BD77-B2EA2612D698", "userdefined7" },
      { userdefined8, "C22705BD-441F-4F37-94B1-11BF7663215B", "userdefined8" },
      { rudder_water_deploy, "2F3FF488-271D-4C6C-9D60-5748BFE73528", "rudder_water_deploy" },
      { mount0, "3014E6E5-53C2-48D9-888C-A7A9404FA35D", "mount0" },
      { mount1, "17B16FEE-2B7F-4BEC-BBFD-C51087AB8679", "mount1" },
      { mount2, "11F715D4-3D4C-4A38-A125-2866B9FCEC07", "mount2" },
      { mount3, "98973A12-B103-4060-90E0-F3A162AEEC40", "mount3" },
      { mount4, "E33A9668-4D20-48D0-92A3-2502FB85C28A", "mount4" },
      { mount5, "401E95EC-5257-4663-91F5-D6EE14AFBEDB", "mount5" },
      { mount6, "2207393B-0C4E-45AE-9160-784B2F316780", "mount6" },
      { mount7, "5C31D892-C1C7-47FA-968F-910FC812EFC3", "mount7" },
      { mount8, "2CEEDE3B-BE3F-4126-9142-12EE10F90F2C", "mount8" },
      { mount9, "1FE69A44-7563-421E-94A4-FD492C0EC076", "mount9" },
      { mount10, "EE6EDD7A-96C5-41DA-BA9B-DC76222FCCB5", "mount10" },
      { bomb_bay, "8DDA5CFF-EADD-4096-A913-7A97848F321F", "bomb_bay" },
      { endcaps1, "8C7090C7-1ECF-4806-8C7D-620C5A59F529", "endcaps1" },
      { endcaps2, "FEE94EF2-4D9E-4FD0-AE51-2D7A280D8EA7", "endcaps2" },
      { c_tire, "4CF550DF-134D-4989-BACD-978E3A69D82E", "c_tire" },
      { l_tire, "4D54624D-D897-4408-876E-1E3E38A253B0", "l_tire" },
      { r_tire, "747D97A8-8770-4FC7-B8F7-1D893A2544BB", "r_tire" },
      { gun0, "BB157DA4-1ADF-47FE-8DDE-2054962A99B1", "gun0" },
      { gun1, "92E2E7E0-A2A9-41A9-8C28-EE3606324B92", "gun1" },
      { gun2, "963A8952-A1B5-4041-BC7B-84BDB8704B93", "gun2" },
      { gun3, "9F0D28CD-A70E-4513-AE09-9B0DB0B683E6", "gun3" },
      { gun4, "D8B13729-E1FC-468A-A068-E6DF4BBF1ACA", "gun4" },
      { gun5, "2EA06A93-FA57-4DC7-A017-770B06B1F6F6", "gun5" },
      { gun6, "FB6FE80B-4B46-4C05-B28E-CC971C441215", "gun6" },
      { gun7, "1F22276D-0E48-439D-864A-8C639EF0EFDC", "gun7" },
      { gun8, "79D725FC-4BCC-421F-85AC-D476257B7233", "gun8" },
      { gun9, "1A896B8F-BD5D-4831-8DFB-3CCA4E3838DD", "gun9" },
      { gun10, "5F42BCD6-885E-4ED6-91DC-D4DEB0CB602D", "gun10" },
      { gun11, "8D800872-F887-468F-8BE3-61081F8857EA", "gun11" },
      { gun12, "6AB0FF52-1AAE-4708-B0CC-3BE3CAE93C13", "gun12" },
      { gun13, "DCE42E61-9477-4E68-B2F4-D845C510F703", "gun13" },
      { gun14, "764CB2FF-4238-4C5E-9C88-C5908239568F", "gun14" },
      { gun15, "AE8F97C1-90F2-4DCE-97D1-23743E054AB6", "gun15" },
      { barrel0, "BB157DA5-1ADF-47FE-8DDE-2054962A99B1", "barrel0" },
      { barrel1, "92E2E7E1-A2A9-41A9-8C28-EE3606324B92", "barrel1" },
      { barrel2, "963A8953-A1B5-4041-BC7B-84BDB8704B93", "barrel2" },
      { barrel3, "9F0D28CC-A70E-4513-AE09-9B0DB0B683E6", "barrel3" },
      { barrel4, "D8B13728-E1FC-468A-A068-E6DF4BBF1ACA", "barrel4" },
      { barrel5, "2EA06A92-FA57-4DC7-A017-770B06B1F6F6", "barrel5" },
      { barrel6, "FB6FE80A-4B46-4C05-B28E-CC971C441215", "barrel6" },
      { barrel7, "1F22276C-0E48-439D-864A-8C639EF0EFDC", "barrel7" },
      { barrel8, "79D725FD-4BCC-421F-85AC-D476257B7233", "barrel8" },
      { barrel9, "1A896B8E-BD5D-4831-8DFB-3CCA4E3838DD", "barrel9" },
      { barrel10, "5F42BCD7-885E-4ED6-91DC-D4DEB0CB602D", "barrel10" },
      { barrel11, "B5134E9E-61F7-4465-96E8-1402C490A99B", "barrel11" },
      { barrel12, "52691558-6D87-48EC-8487-70CF577305CB", "barrel12" },
      { barrel13, "E98D5341-537E-46A6-AD4A-4346362ED161", "barrel13" },
      { barrel14, "C22CA53D-E99B-4BB3-AC5B-50AF0621DD93", "barrel14" },
      { barrel15, "C00A18A4-365C-4FE3-B85F-FCD946A3E57E", "barrel15" },
      { damaged0, "61CD257A-75C5-410D-9046-6297290FCB1E", "damaged0" },
      { bullets0, "E616DD47-B038-4A47-A955-8D7C93ED99C0", "bullets0" },
      { bullets1, "1BAEF42B-7D43-451A-9BBD-E2BC77672CF4", "bullets1" },
      { bullets2, "CB3630A7-8CF5-4C03-9BB0-A573F8B0288A", "bullets2" },
      { bullets3, "D39A7A59-4FD9-43F6-B170-6CDFFDC455DD", "bullets3" },
      { bullets4, "7664E098-29B8-4247-8886-ECC08BF9979B", "bullets4" },
      { bullets5, "646F6809-8078-4B29-9719-6D2736772E06", "bullets5" },
      { bullets6, "8D0E50B9-5F1E-405A-A0FE-3D39DEF3848A", "bullets6" },
      { bullets7, "D7CD3343-7D09-4902-9B49-69D0FC807A1D", "bullets7" },
      { pylon, "064B87DD-3BCC-4437-BFB5-0994F76A346B", "pylon" },
      { cockpit_detail, "A75645F6-2099-4104-8882-9610A08A9587", "cockpit_detail" },
      { battery_switch, "055E806F-80C0-4CDB-A97F-5C97067DB2E8", "battery_switch" },
      { l_pct_lead_edge_flap0, "9059F46F-C39F-40A2-A755-CC0DA0C86655", "l_pct_lead_edge_flap0" },
      { r_pct_lead_edge_flap0, "DD8A8509-BC82-4C0B-B1E0-F4DD19ABE771", "r_pct_lead_edge_flap0" },
      { l_pct_lead_edge_flap1, "27D0C527-C065-4BC9-B440-30B2B869DAD1", "l_pct_lead_edge_flap1" },
      { r_pct_lead_edge_flap1, "5034B894-4D38-4B3A-9934-B473B56868FB", "r_pct_lead_edge_flap1" },
      { l_pct_trail_edge_flap0, "7E318347-9423-4434-A724-F34E920BFF51", "l_pct_trail_edge_flap0" },
      { r_pct_trail_edge_flap0, "8E847B06-1687-4430-A29C-8316075AFBEA", "r_pct_trail_edge_flap0" },
      { l_pct_trail_edge_flap1, "FB000AC3-B831-4370-B516-607FB7D77EEB", "l_pct_trail_edge_flap1" },
      { r_pct_trail_edge_flap1, "7A2DD649-2071-4A8A-A0C7-F7212B553654", "r_pct_trail_edge_flap1" },
      { thrust_reverser0, "14627CC7-99CD-4F10-9078-2BF54687159E", "thrust_reverser0" },
      { thrust_reverser1, "B6C1AFF6-4FB9-4983-83E0-085406758DAB", "thrust_reverser1" },
      { thrust_reverser2, "8A4A1687-6AC4-43E6-8298-06E9B336E12C", "thrust_reverser2" },
      { thrust_reverser3, "7FCA23E8-B0E9-405D-9177-7E73A5E448A9", "thrust_reverser3" },
      { lever_throttle0, "07A849C0-217F-4BC7-B000-CAEE1C2B6A4F", "lever_throttle0" },
      { lever_throttle1, "B807C87B-B5D6-4E53-8FD6-CAAE2B98C1AE", "lever_throttle1" },
      { lever_throttle2, "97CF9D57-79F0-4ACE-83AE-DEFD02DECFE8", "lever_throttle2" },
      { lever_throttle3, "A938FEBD-5B60-4F8D-8FEA-F8CE7DEF84B4", "lever_throttle3" },
      { lever_prop_pitch0, "4D80B638-0F68-4177-8DCA-8BF9D51ADB8A", "lever_prop_pitch0" },
      { lever_prop_pitch1, "6A9D7487-17C1-47DF-B8FB-A0D170CCB649", "lever_prop_pitch1" },
      { lever_prop_pitch2, "A32DE5BF-E15D-49B0-97E7-012E7E52FA4D", "lever_prop_pitch2" },
      { lever_prop_pitch3, "5C0C1ED8-745B-49F0-9C55-CB430D7C3015", "lever_prop_pitch3" },
      { lever_mixture0, "A53C0EB7-3DA8-4026-A245-4723B6027919", "lever_mixture0" },
      { lever_mixture1, "FED13262-B09F-4992-96E0-65FCE645AA14", "lever_mixture1" },
      { lever_mixture2, "CF873F5B-421F-446E-B5CC-3DA7A559F05C", "lever_mixture2" },
      { lever_mixture3, "6424EA9A-CB8F-4AAC-93B3-B522A41B729C", "lever_mixture3" },
      { lever_water_rudder, "98DCDD0E-3392-4DCC-BC0D-A1237DF13DA2", "lever_water_rudder" },
      { lever_stick_fore_aft, "5DCB06D5-B974-4559-829D-1A562499CECD", "lever_stick_fore_aft" },
      { lever_stick_l_r, "76E3ECA3-6F10-42AA-8929-1DD26FCD1926", "lever_stick_l_r" },
      { lever_pedals_l_r, "B0A58FCC-C3E2-4798-8E32-B2A1C8C59FE8", "lever_pedals_l_r" },
      { lever_collective, "6FA6931D-9DBC-4F79-9379-0423AF21229E", "lever_collective" },
      { lever_landing_gear, "4488B91F-1B47-4FCA-A1DD-C198942026C9", "lever_landing_gear" },
      { lever_speed_brake, "26281451-7FA3-4AA4-9152-FD47E590E7AE", "lever_speed_brake" },
      { lever_parking_brake, "BF5E3952-36A1-49FE-A7A4-7F705C17D9A1", "lever_parking_brake" },
      { lever_flap, "D9BD6CCD-E95A-485A-B6E3-323E2CA055E6", "lever_flap" },
      { lever_cowl_flaps0, "FC47236C-B2F1-4975-A81B-9267EF4F99B9", "lever_cowl_flaps0" },
      { lever_cowl_flaps1, "F91CCED0-D5BF-4DF1-AD3D-DF82747AEF78", "lever_cowl_flaps1" },
      { lever_cowl_flaps2, "A34A7CC3-B559-47EE-8960-2C01F9A9733C", "lever_cowl_flaps2" },
      { lever_cowl_flaps3, "C0CA78D9-306E-42AB-A0C2-C2F0E895E0C9", "lever_cowl_flaps3" },
      { cowl_flaps0, "19B17809-5BA2-4E4D-823F-F540A80C8496", "cowl_flaps0" },
      { cowl_flaps1, "76DF1AEC-DD93-4E86-A050-DD96CAEF3907", "cowl_flaps1" },
      { cowl_flaps2, "9E630331-990E-4CAD-B68E-427193F71DDF", "cowl_flaps2" },
      { cowl_flaps3, "50F91975-920A-4107-8E64-4151A3583C3B", "cowl_flaps3" },
      { aux_gear, "B9DD91D6-6556-41DA-922F-AB671437990F", "aux_gear" },

   };

   static const int NUM_AIRCRAFT_PARAMS = 165;

} // End namespace BGL
} // End namespace Assimp

#endif // BGL_H
