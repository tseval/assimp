#ifndef BGLPARSER_H
#define BGLPARSER_H

#include <list>
#include "BGL.h"
#include <cstdio>
#include "Streamreader.h"

namespace Assimp
{
namespace BGL
{
//===========================================================================
/** BGLParser - BGL Graphics language parser.
 * This class is a simple parser for the BGL graphics language defined by
 * Microsoft(R) for use in the Microsoft Flight Simulator(TM).
 *
 * The parser is able to read both .bgl (scenery) and .mdl (aircraft model)
 * files. To use the parser class in your application, inherit the BGLParser
 * class and implement the relevant BGL commands using the interface described
 * by this class. Each of the interface methods are called in the order they
 * appear in the BGL file with the correct parameters as specified in the
 * file.
 *
 * None of the interface methods will do anything by default with a
 * few exceptions (see below), so you have to implement these methods
 * yourself for your own needs. You can use a set of utility methods
 * in the parser class to parse the various parameters and to control
 * the flow of the parsing.
 *
 * \author Thomas Sevaldrud <thomas@silentwings.no>
 */
//===========================================================================

class BGLParser
{
protected:

   // File Address Stack
   std::list<long> 	stack_;

   // Opcode stack
   std::list<unsigned short> opcode_stack_;

   // File header
   FILE_HEADER2 hdr_;

   // File handle
   boost::shared_ptr<StreamReaderLE> reader_;

   double unit_scale_;

   Var32 var_base32_;

   bool done_;

   LLA readLLA();
   SIF48 readSIF48();
   Angl48 readAngl48();
   UNICOL readUNICOL();
   XYZ16 readXYZ16();
   XZ16 readXZ16();
   PBH16 readPBH16();
   PXZ16 readPXZ16();
   GUid128 readGUID128();
   VERTEX readVERTEX();
   GVERTEX readGVERTEX();
   XYZF32 readXYZF32();
   MATERIAL readMATERIAL();
   TEXTURE readTEXTURE();
   UInt32 readFourCC();
   void readBytes(char *buf, int count);

   /// Remove whitespace and convert to lowercase
   void cvtFileString(const STRINGZ* src, STRINGZ* dst, int length);

   /// Read null-terminated string of even length, possibly padded with a 0.
   void readStringZ(STRINGZ* str, int length);

   /// Call subroutine at relative address addr.
   void callSub(long addr);

   /// Unconditionally jump to relative addr
   void jump(long addr);

public:

   /** Constructor.
    * Detailed description.
    */
   BGLParser(StreamReaderLE *reader);
   BGLParser(boost::shared_ptr<StreamReaderLE> reader);

   /** Destructor.
    * Detailed description.
    */
   virtual ~BGLParser();

   void parseOpcode(Enum16 opcode);

   /** BGL_EOF (0x00).
    * End of file. Parsing stops here.
    * \param opcode Opcode number of this command.
    */
   virtual void BEOF(Enum16 opcode);

   /** BGL_OBSOLETE (opcode varies).
    * \param opcode Opcode number of this command.
    */
   virtual void OBSOLETE(Enum16 opcode);

   /** BGL_RESERVED.
    * \param opcode Opcode number of this command.
    */
   virtual void RESERVED(Enum16 opcode);

   /// No operation (opcode = 0x02).
   virtual void NOOP(Enum16 opcode);

   /** BGL_CASE (0x03).
    * This is really a jump table starting at 0 for N entries. If the
    * value of the variable is outside that range (< 0 or > N-1), the
    * fail entry is used. All jump addresses are relative to the start
    * of the case.
    *
    * \param opcode Opcode number of this command.
    * \param number Number of cases.
    * \param token Index of the variable or offset in local variables
    *              of the variable to use as an index into the jump table
    * \param fail_jump Relative offset if the case fails.
    * \param jumps[number] Relative jump table.
    */
   virtual void CASE(Enum16 opcode,
                     UInt16 number,
                     SInt16 token,
                     SInt16 fail_jump,
                     SInt16 jumps[]);

   /** BGL_SURFACE (0x05).
    * Defines the beginning of a convex non-light source, shaded
    * surface (polygon). Polygons are convex unless proceeded by a
    * BGL_CONCAVE. This command is not normally used. If this is used,
    * it should only be used for polygons flat on the ground. This
    * might be followed by STRRES, CNTRES, &, CLOSURE to complete the
    * definition of the polygon.
    * \param opcode Opcode number of this command.
    */
   virtual void SURFACE(Enum16 opcode);

   /** BGL_SPNT (0x06).
    * Starts line definition. Only use this command for line drawing,
    * not surface definition.
    *
    * Use convertPoint() to get scaled and transformed xyz coordinates
    * relative to the current transform and scaling parameters.
    *
    * \param opcode Opcode number of this command.
    * \param point  Coordinates of the point in 16-bits MSFS coordinates.
    *
    * \see convertPoint().
    */
   virtual void SPNT(Enum16 opcode, XYZ16 point);

   /** BGL_CPNT (0x07).
    * Continues a line definition. Only use this command for line
    * drawing, not surface definition.
    *
    * Use convertPoint() to get scaled and transformed xyz coordinates
    * relative to the current transform and scaling parameters.
    *
    * \param opcode Opcode number of this command.
    * \param point  Coordinates of the point in 16-bits MSFS coordinates.
    *
    * \see convertPoint().
    */
   virtual void CPNT(Enum16 opcode, XYZ16 point);

   /** BGL_CLOSURE (0x08).
    * Completes the definition of a polygon (closes and thereby
    * connects the last point back to the start point).
    *
    * \param opcode Opcode number of this command.
    */
   virtual void CLOSURE(Enum16 opcode);

   /** BGL_JUMP (0x0D).
    * Unconditionally continues processing at new address in the
    * current BGL object. CANNOT JUMP across different objects.
    *
    * \param opcode Opcode number of this command.
    * \param jump   Relative offset within the current object to jump to.
    */
   virtual void JUMP(Enum16 opcode, SInt16 jump);

   /** BGL_DEFRES (0x0E).
    * Defines a vertex in a list of vertices (points) to be used
    * later. The current list is limited to 2048 entries.
    *
    * Use convertPoint() to get scaled and transformed xyz coordinates
    * relative to the current transform and scaling parameters.
    *
    * \param opcode Opcode number of this command.
    * \param index Index of the vertex to define.
    * \param vertex Defines the vertex in XYZ space relative to the
    *               last scale command in the current scale units.
    *
    * \see convertPoint().
    */
   virtual void DEFRES(Enum16 opcode, UInt16 index, XYZ16 vertex);

   /** BGL_STRRES (0x0F).
    * Starts a line or polygon definition. If this is used to start a
    * polygon definition, it will be a non-light source shaded polygon
    * and should be flat on the ground. See BGL_SURFACE (0x05) for
    * other information.
    *
    * \param opcode Opcode number of this command.
    * \param index Index into the vertex list of the vertex.
    *
    * \see BGL_SURFACE
    */
   virtual void STRRES(Enum16 opcode, UInt16 index);

   /** BGL_CNTRES (0x10).
    * Continues a line or polygon definition. If this is used for a
    * polygon, see BGL_STRRES (0x0F) and BGL_SURFACE (0x05).
    *
    * \param opcode Opcode number of this command.
    * \param index Index into the vertex list of the vertex.
    *
    * \see BGL_STRRES
    * \see BGL_SURFACE
    */
   virtual void CNTRES(Enum16 opcode, UInt16 index);

   /** BGL_SCOLOR (0x14).
    * Sets the color of polygon(s) to follow. This is a color from
    * pre-defined table of colors. (Same as COLOR (0x50)). This is for
    * non-textured polygons.
    *
    * Use convertColor() to get the RGBA values for the given color
    * index.
    *
    * \param opcode Opcode number of this command.
    * \param color  Index of the wanted color.
    *
    * \see BGL_COLOR
    * \see convertColor().
    */
   virtual void SCOLOR(Enum16 opcode, UInt16 color);

   /** BGL_ELEVATION_MAP (0x15).
    * Defines a grid (checker board) to make uneven terrain elevated
    * ground. A scale command should have already been run. The texture
    * should already be set. This is the old way of doing ground
    * terrain and should not be used anymore. This will not be
    * supported after version 7.00.
    *
    * \param opcode Opcode number of this command.
    * \param grid_size_x number of columns in the grid.
    * \param grid_size_z number of rows in the grid.
    * \param square_size_x size of each square of the grid in the X
    *                      direction in SCALE units.
    * \param square_size_z size of each square of the grid in the Z
    *                      direction in SCALE units.
    * \param starting_x starting X displacement of the grid from the
    * scale center to the lower left corner of this grid in SCALE
    * units (Usually this is (square_size_x * grid_size_x / 2))
    * \param starting_z starting Z displacement of the grid from the
    * scale center to the lower left corner of this grid in SCALE
    * units (Usually this is (square_size_z * grid_size_z / 2))
    * \param min_altitude Minimum altitude of the entire map in Meters
    * \param max_altitude Maximum altitude of the entire map in Meters.
    * \param elevation_points [3][grid_size_x + 1][grid_size_z + 1]
    * Elevation and texture coordinates for each of the grid squares
    * by rows starting with the lower left corner. Elevation_point
    * [0][?]]?] is the X texture coordinate Elevation_point [1][?]]?]
    * is the Z texture coordinate Elevation_point [2][?]]?] is the
    * altitude in Meters
    */

   virtual void ELEVATION_MAP(Enum16 opcode,
                              UInt16 grid_size_x,
                              UInt16 grid_size_y,
                              UInt16 square_size_x,
                              UInt16 square_size_z,
                              SInt16 starting_x,
                              SInt16 starting_z,
                              SInt16 min_altitude,
                              SInt16 max_altitude,
                              const SInt16* elevation_points);

   /** BGL_TEXTURE_ENABLE (0x17).
    * Enables and disables texturing. This is a way to texture one or
    * more surfaces (polygons) of an objects and then flat or gouraud
    * shade one of more surfaces after. It can also be used to turn
    * texturing back on, but this is very tricky.
    *
    * \param opcode Opcode number of this command.
    * \param onoff 0 turns texturing off, 1 turns texturing back on
    */
   virtual void TEXTURE_ENABLE(Enum16 opcode, Bool16 onoff);

   /** BGL_TEXTURE (0x18).
    * Loads a texture map to cover a surface (polygon). This is also an
    * implied BGL_SURFACE. This is being phased out; please use
    * BGL_TEXTURE2 (0x43).
    *
    * \param opcode Opcode number of this command.
    * \param index internal index MUST BE 0.
    * \param bias_x bias to X coordinates.
    * \param free unused.
    * \param bias_z bias to Z coordinates.
    * \param name[13] filename of the texture. Must be padded out to
    * 13 characters, but does not have to be strict MS-DOS 8.3.
    *
    * \see BGL_TEXTURE2
    */
   virtual void TEXTURE1(Enum16 opcode,
                         UInt16 index,
                         SInt16 bias_x,
                         SInt16 free,
                         SInt16 bias_z,
                         const STRINGZ* name);

   /** BGL_PALETTE (0x19).
    * Load a palette file that defines colors to be used with old RAW
    * (indexed) style texture files. Only the last 64 index slot
    * (colors) are loaded. Please discontinue using indexed texture
    * files and palettes as soon as possible and switch to BMP
    * files. This will not be supported after version 7.00.
    *
    * \param opcode Opcode number of this command.
    * \param name[13] filename of the palette. Must be padded out to
    * 13 characters, but does not have to be strict MS-DOS 8.3.
    */
   virtual void PALETTE(Enum16 opcode,
                        const STRINGZ* name);

   /** BGL_RESLIST (0x1A).
    * Defines a list of vertices to be used to draw lines, polygon,
    * etc. The current limitation is 2048 vertices.
    *
    *
    * Use convertPoint() to get scaled and transformed xyz coordinates
    * relative to the current transform and scaling parameters.
    *
    * \param opcode Opcode number of this command.
    * \param start_index starting index to define vertices (points).
    * \param count number of vertices to define.
    * \param vertex[count] define vertex XYZ relative to the last
    * SCALE command
    *
    * \see convertPoint().
    */
   virtual void RESLIST(Enum16 opcode,
                        UInt16 start_index,
                        UInt16 count,
                        const XYZ16* vertex);


   /** BGL_IFIN_BOX_RAW_PLANE (0x1B).
    * If the user s plane is inside this rectangle, fall through to the
    * next command. This box is not rotated with instance type
    * commands.
    */
   virtual void IFIN_BOX_RAW_PLANE(Enum16 opcode,
                                   SInt16 fail,
                                   XYZ16 center,
                                   XYZ16 size,
                                   PBH16 rotation);

   /** BGL_IFIN2 (0x1C).
    * Checks whether 2 specified variables are each within their own
    * specific bounds. If low1 <= var1 <= high1 and low2 <= var2 <= high2.
    */
   virtual void IFIN2(Enum16 opcode,
                      SInt16 fail,
                      Var16 var1,
                      SInt16 low1,
                      SInt16 high1,
                      Var16 var2,
                      SInt16 low2,
                      SInt16 high2);

   /** BGL_FACE (0x1D).
    * Light source shaded surface (polygon) with a normal and point for
    * backface culling. It is easier and a little better to use a FACET
    * command. This is a convex polygon unless it is preceded by a
    * CONCAVE command.
    */
   virtual void FACE(Enum16 opcode,
                     UInt16 count,
                     XYZ16 point,
                     XYZ16 normal,
                     const UInt16* vertices);

   /** BGL_HAZE (0x1E).
    * Allows a texture to have transparent pixels in it. If the color
    * index value of a pixel in the texture is dthe value the pixel is
    * not copied, i.e., transparent. If the value is 0, then there is
    * no transparency and all pixels are copied. This only works with
    * .R8 textures and should not be used anymore. This will not be
    * supported after version 7.00.
    */
   virtual void HAZE(Enum16 opcode,
                     UInt16 factor);


   /** BGL_FACET_TMAP (0x20).
    * Textured surface (polygon) with a normal and reference value for
    * backface culling. Each vertex on the polygon also has a texture
    * coordinate associated with it. This is a convex polygon unless it
    * is preceded by a CONCAVE command.
    */
   virtual void FACET_TMAP(Enum16 opcode,
                           UInt16 count,
                           XYZ16 normal,
                           SInt32 dot_ref,
                           const PXZ16* vertices);

   /** BGL_IFIN3 (0x21).
    * These are 3 specified variables, each within their own specific
    * bounds. If low1 <= var1 <= high1 and low2 <= var2 <= high2 and
    * low3 <= var3 <= high3.
    */
   virtual void IFIN3(Enum16 opcode,
                      SInt16 fail,
                      Var16  var1,
                      SInt16 low1,
                      SInt16 high1,
                      Var16  var2,
                      SInt16 low2,
                      SInt16 high2,
                      Var16  var3,
                      SInt16 low3,
                      SInt16 high3);

   /** BGL_RETURN (0x22).
    * Return from a subroutine
    */
   virtual void RETURN(Enum16 opcode);

   /** BGL_CALL (0x23).
    * Subroutine call starts processing at new address by nesting in
    * the current BGL object. BGL_RETURN from the subroutine will
    * continue processing at the next command. CANNOT CALL across
    * different objects.
    */
   virtual void CALL(Enum16 opcode,
                     SInt16 call);

   /** BGL_IFIN1 (0x24).
    * Checks whether a specified variable is within specific bounds. If
    * low <= var <= high.
    */
   virtual void IFIN1(Enum16 opcode,
                      SInt16 fail,
                      Var16  var,
                      SInt16 low,
                      SInt16 high);


   /** BGL_SEPARATION_PLANE (0x25).
    * Normal vector with a dot product reference used to decide which
    * side of an imaginary plane the eye is on.
    */
   virtual void SEPARATION_PLANE(Enum16 opcode,
                                 SInt16 alternate_jump,
                                 XYZ16 normal,
                                 SInt32 dot_ref);

   /** BGL_SETWRD (0x26).
    * Sets the value of a local or global variable. This is always a
    * 16-bit variable. There are a limited number of global variables
    * that should be written. Make sure that others are not written.
    */
   virtual void SETWRD(Enum16 opcode,
                       Var16  var1,
                       SInt16 value);

   /** BGL_GRESLIST (0x29).
    * Defines a list of vertices (points) and normals to draw lines,
    * polygons, etc. The current limitation is 2048 vertices.
    */
   virtual void GRESLIST(Enum16 opcode,
                         UInt16 start_index,
                         UInt16 count,
                         const GVERTEX* vertex);


   /** BGL_GFACET (0x2A).
    * Gouraud shaded surface (polygon) with a normal and reference
    * value for backface culling. This is a convex polygon unless it is
    * preceded by a CONCAVE command.
    */
   virtual void GFACET(Enum16 opcode,
                       UInt16 count,
                       XYZ16 normal,
                       SInt32 dot_ref,
                       const UInt16* vertices);

   /** BGL_ADDOBJ32 (0x2B).
    * Add an object to the radsort list to be displayed later with
    * other 3D objects. Any 3D object that sticks up from the ground
    * should be ADDOBJ(32)ed so it can be sorted and displayed with all
    * other 3D. Any ADDOBJ(32) object must start with a SCALE command
    * and end with a BGL_RETURN.
    */
   virtual void ADDOBJ32(Enum16 opcode,
                         SInt32 call);

   /** BGL_REJECT (0x2C).
    * Determines if any part of a sphere is viewable on the screen.
    */
   virtual void REJECT(Enum16 opcode,
                       SInt16 fail,
                       XYZ16 center,
                       UInt16 radius);

   /** BGL_SCOLOR24 (0x2D).
    * Sets the color of polygon(s) to follow.
    */
   virtual void SCOLOR24(Enum16 opcode,
                         UNICOL color);


   /** BGL_LCOLOR24 (0x2E).
    * Sets the color of line(s) to follow.
    */
   virtual void LCOLOR24(Enum16 opcode,
                         UNICOL color);


   /** BGL_SCALE (0x2F).
    * Defines a LATLONALT anchor point and design scale to use to draw
    * objects.
    */
   virtual void SCALE(Enum16 opcode,
                      SInt16 fail,
                      UInt16 range,
                      UInt16 size,
                      Var16 index,
                      UInt32 scale,
                      LLA lla);

   /** BGL_RESROW (0x31).
    * Defines a list of vertices (points) in a row from the two end
    * points.
    */
   virtual void RESROW(Enum16 opcode,
                       UInt16 start_index,
                       UInt16 count,
                       XYZ16 starting_point,
                       XYZ16 ending_point);

   /** BGL_ADDOBJ (0x32).
    * Add an object to the radsort list to be displayed later with
    * other 3D objects. Any 3D object that sticks up from the ground
    * should be ADDOBJ(32)ed so it can be sorted and displayed with all
    * other 3D objects. Any ADDOBJ(32) object must start with a SCALE
    * command and end with a BGL_RETURN.
    */
   virtual void ADDOBJ(Enum16 opcode,
                       SInt16 call);

   /** BGL_INSTANCE (0x33).
    * This command will rotate all points around a scale center in all
    * three axes (pitch, bank, & heading).
    */
   virtual void INSTANCE(Enum16 opcode,
                         SInt16 call,
                         PBH16 rotation);

   /** BGL_SUPER_SCALE (0x34).
    * Defines the design scale units to be used in an object. This must
    * be preceded by a POSITION or VPOSITION command. This is typically
    * used for moving objects like the user s plane and dynamic
    * scenery. It should NOT be used for fixed 3D objects. This is
    * similar to a SCALE command.
    */
   virtual void SUPER_SCALE(Enum16 opcode,
                            SInt16 fail,
                            UInt16 range,
                            UInt16 size,
                            UInt16 super_scale);

   /** BGL_PNTROW (0x35).
    * Defines a row of points in a row using the two end points. These
    * points will be displayed as a row of lights.
    */
   virtual void PNTROW(Enum16 opcode,
                       XYZ16 starting_point,
                       XYZ16 ending_point,
                       UInt16 count);

   /** BGL_POINT (0x37).
    * Defines a point (light).
    */
   virtual void POINT(Enum16 opcode,
                      XYZ16 point);


   /** BGL_CONCAVE (0x38).
    * All polygons are convex unless they are proceeded by this
    * command. This command should not be used because the result is
    * slower and may not be predictable.
    */
   virtual void CONCAVE(Enum16 opcode);

   /** BGL_IFMSK (0x39).
    * Used to determine if a set of bits in a variable are set or
    * not. The variable is bit wise ANDed with a constant mask (value
    * or bit pattern); if the result is non-zero it will fall through
    * to the next command; if it is zero it will jump to the relative
    * fail address.
    */
   virtual void IFMSK(Enum16 opcode,
                      SInt16 fail,
                      Var16 var,
                      Var16 mask);

   /** BGL_VPOSITION (0x3A).
    * Used to set the anchor location of an object. This anchor
    * location is in Latitude, Longitude, and Altitude. Only used with
    * SUPER_SCALE and moving objects such as user aircraft or dynamic
    * scenery. The LATLONALT is located in local variables for the
    * object. This is the same as a POSITION except the LATLONALT is in
    * a variable array.
    */
   virtual void VPOSITION(Enum16 opcode,
                          SInt16 fail,
                          UInt16 range,
                          UInt16 size,
                          Var16 index,
                          Var16 var);

   /** BGL_VINSTANCE (0x3B).
    * This command will rotate all points around a scale center in all
    * three axes (pitch, bank, & heading). This is the same as INSTANCE
    * except the pitch, bank, and heading are in a variable array.
    */
   virtual void VINSTANCE(Enum16 opcode,
                          SInt16 call,
                          Var16  var);

   /** BGL_POSITION (0x3C).
    * Used to set the anchor location of an object. This anchor
    * location is in Latitude, Longitude, and Altitude. Only used with
    * SUPER_SCALE and fixed objects with very high detail such as
    * aircraft. This is the same as a VPOSITION except the LATLONALT is
    * within the command.
    */
   virtual void POSITION(Enum16 opcode,
                         SInt16 fail,
                         UInt16 range,
                         UInt16 size,
                         Var16 index,
                         LLA lla);

   /** BGL_SEED (0x3D)
    * Defines a hole in the terrain. This used to be for seeds, but now
    * only works for hole seeds. Even hole seeds will not be supported
    * after version 7.00.
    */
   virtual void SEED(Enum16 opcode);

   /** BGL_FACET (0x3E).
    * Light source shaded surface (polygon) with a normal and dot
    * reference for backface culling. The normal is also used to
    * determine the light source angle on the surface.
    */
   virtual void FACET(Enum16 opcode,
                      UInt16 count,
                      XYZ16 normal,
                      SInt32 dot_ref,
                      const UInt16* vertices);

   /** BGL_SHADOW_CALL (0x3F).
    * Unconditionally processed at new address by nesting the current
    * BGL object in shadow mode. This should only be done on objects
    * that stick up from the ground that cause shadows. This cannot be
    * inside ADDOBJed code. BGL_RETURN from the subroutine will
    * continue processing at the next command. CANNOT SHADOW_CALL
    * across different objects.
    */
   virtual void SHADOW_CALL(Enum16 opcode,
                            SInt16 call);

   /** BGL_SHADOW_VPOSITION (0x40).
    * Used to set the anchor location of an object s shadow. This
    * anchor location is in Latitude, Longitude, and Altitude. This is
    * usually used with SHADOW_VICALL and SUPER_SCALE and moving
    * objects such as user aircraft or dynamic scenery. The LATLONALT
    * is located in local variables for the object. This has the same
    * parameters and format as VPOSITION.
    */
   virtual void SHADOW_VPOSITION(Enum16 opcode,
                                 SInt16 fail,
                                 UInt16 range,
                                 UInt16 size,
                                 Var16 index,
                                 Var16 vlla);

   /** BGL_SHADOW_VICALL (0x41).
    * This command will rotate all points around a shadow scale center
    * in all three axes (pitch, bank, & heading). This is the same as
    * VINSTANCE except it is for the shadow.
    */
   virtual void SHADOW_VICALL(Enum16 opcode,
                              SInt16 call,
                              Var16 vpbh);


   /** BGL_POYLGON_RUNWAY (0x42).
    * This command will generate a complete textured runway. This is
    * exactly the same as TEXTURE_RUNWAY (0x44) and will be textured
    * the same. Runway s base end is the south end of an un-rotated
    * runway. All runway measurements are in feet. Please use the newer
    * runway command NEW_RUNWAY (0xAA). This will not be supported
    * after version 7.00.
    */
   virtual void POLYGON_RUNWAY(Enum16 opcode,
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
                               SInt16 recip_vasi_spacing);

   /** BGL_TEXTURE2 (0x43).
    * Loads a texture map to cover a surface (polygon). This is also an
    * implied BGL_SURFACE.
    */
   virtual void TEXTURE2(Enum16 opcode,
                         UInt16 length,
                         UInt16 index,
                         Flags8 characteristics,
                         UInt8 checksum,
                         UNICOL color,
                         const STRINGZ* name);

   /** BGL_TEXTURE_RUNWAY (0x44).
    * This command will generate a complete textured runway. This is
    * exactly the same as POLYGON_RUNWAY (0x42). Runway s base end is
    * the south end of an un-rotated runway. All runway measurements
    * are in feet. Please use the newer runway command NEW_RUNWAY
    * (0xAA). This will not be supported after version 7.00.
    */
   virtual void TEXTURE_RUNWAY(Enum16 opcode,
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
                               SInt16 recip_vasi_spacing);

   /** BGL_POINT_VICALL (0x46).
    * This command will rotate all points around a point offset from
    * the scale center in all three axes (pitch, bank, & heading).
    */
   virtual void POINT_VICALL(Enum16 opcode,
                             SInt16 call,
                             XYZ16 offset,
                             Angl16 pitch,
                             SInt16 vpitch,
                             Angl16 bank,
                             SInt16 vbank,
                             Angl16 heading,
                             SInt16 vheading);

   /** BGL_Var_SEG (0x48).
    * This will reset the variable access class back to GLOBAL.
    */
   virtual void Var_SEG(Enum16 opcode,
                        UInt16 dummy);

   /** BGL_BUILDING (0x49).
    * This is use to draw generic buildings. We are trying to phase
    * this command out and would prefer that the BGL_OBJECT (0xA0) be
    * used instead. This assumes a SCALE in meter units has already
    * been done. If this building is to be rotated, an INSTANCE command
    * should already be done. This will not be supported after version
    * 7.00.
    */
   virtual void BUILDING(Enum16 opcode,
                         Flags16 info,
                         Flags16 codes,
                         XYZ16 offset,
                         UInt16 stories,
                         UInt16 size_x,
                         UInt16 size_z);

   /** BGL_VSCALE (0x4C).
    * Defines a LATLONALT anchor point and design scale to use to draw
    * objects. The LATLONALT is pointed to by a variable.
    */
   virtual void VSCALE(Enum16 opcode,
                       SInt16 fail,
                       UInt16 range,
                       UInt16 size,
                       Var16 index,
                       UInt32 scale,
                       SInt16 vlla);

   /** BGL_MOVE_L2G (0x4D).
    * Move a word from local variables to global variables.
    */
   virtual void MOVE_L2G(Enum16 opcode,
                         UInt16 global,
                         SInt16 local);


   /** BGL_MOVE_G2L (0x4E).
    * Move a word from global variables to local variables.
    */
   virtual void MOVE_G2L(Enum16 opcode,
                         SInt16 local,
                         UInt16 global);

   /** BGL_MOVEWORD (0x4F).
    * Moves a word from a global variable to a global variable.
    */
   virtual void MOVEWORD(Enum16 opcode,
                         SInt16 to,
                         SInt16 from);

   /** BGL_GCOLOR (0x50).
    * Sets the color of polygon(s) to follow. This is a color from
    * pre-defined table of colors. (Same as SCOLOR (0x14)). Trying to
    * phase this command out, so use SCOLOR (0x14).
    */
   virtual void GCOLOR(Enum16 opcode,
                       Var16 color);

   /** BGL_NEW_LCOLOR (0x51).
    * Sets the color of lines to follow. Resets brightness to
    * full. Same as LCOLOR
    */
   virtual void NEW_LCOLOR(Enum16 opcode,
                           Var16 color);

   /** BGL_NEW_SCOLOR (0x51).
    * Sets the color of polygon(s) to follow. This is a color from
    * pre-defined table of colors. Resets brightness to full.
    */
   virtual void NEW_SCOLOR(Enum16 opcode,
                           Var16 color);

   /** BGL_SURFACE_TYPE (0x55).
    * Sets the surface type of the ground the aircraft is on. Checks to
    * see if the user s aircraft is on the ground and within a block
    * centered at the current SCALE command. This command only works in
    * the ground database in the miscellaneous section.
    */
   virtual void SURFACE_TYPE(Enum16 opcode,
                             Enum8 surface_type,
                             Enum8 surface_condition,
                             UInt16 size_x,
                             UInt16 size_z,
                             UInt16 altitude);

   /** BGL_SET_WEATHER (0x56).
    * Used to set weather information for ridge lifts and thermals. If
    * there is more than one weather section in the active BGL objects,
    * the last one will be the one used. Which object is the last one
    * is random.
    */
   virtual void SET_WEATHER(Enum16 opcode,
                            UInt16 length);


   /** BGL_WEATHER (0x57).
    * This is the command that defines ridge lift or thermals. The must
    * be within a SET_WEATHER section in a BGL object. There also needs
    * to be other BGL code before this command to determine if the user
    * s plane is in this weather area. This might be done with a
    * combination of SCALE and IFINBOXPs.
    */
   virtual void WEATHER(Enum16 opcode,
                        Enum8 fixed,
                        Enum8 type,
                        Angl16 heading,
                        UInt16 scalar,
                        UInt16 extra);

   /** BGL_TEXTURE_BOUNDS (0x58).
    * Sets the bounds (edges) of a texture when it is being used with a
    * non-coordinate type polygon command such as STRRES, CNTRES. This
    * will not be supported after version 7.00.
    */
   virtual void TEXTURE_BOUNDS(Enum16 opcode,
                               UInt32 lower_x,
                               UInt32 lower_z,
                               UInt32 upper_x,
                               UInt32 upper_z);

   /** BGL_TEXTURE_REPEAT (0x5D).
    * If the previous texture loading command was successful, this will
    * turn texturing back on. This is mostly used with SURFACE, STRRES,
    * CNTRES. This will not be supported after version 7.00. Length 8
    * bytes Enum16 opcode BGLOP_TEXTURE_REPEAT = 0x5D SInt16 bias_x
    * bias to X coordinates SInt16 free unused SInt16 bias_z bias to Z
    * coordinates
    */
   virtual void TEXTURE_REPEAT(Enum16 opcode,
                               SInt16 bias_x,
                               SInt16 free,
                               SInt16 bias_z);

   /** BGL_IFSIZEV (0x5F).
    * This command can be used to determine how big an object is on the
    * screen. If real_size in Meters converted to vertical pixels on
    * the screen is less than the number of pixels in pixels_ref, then
    * branch to the smaller relative address.
    */
   virtual void IFSIZEV(Enum16 opcode,
                        SInt16 smaller,
                        UInt16 real_size,
                        UInt16 pixels_ref);

   /** BGL_FACE_TMAP (0x60).
    * Textured light source shaded surface (polygon) that with a normal
    * and point for backface culling. It is easier and a little better
    * to use a FACET_TMAP command. This is a convex polygon unless it
    * is preceded by a CONCAVE command.
    */
   virtual void FACE_TMAP(Enum16 opcode,
                          UInt16 count,
                          XYZ16 point,
                          XYZ16 normal,
                          const PXZ16* vertices);

   /** BGL_IFVIS (0x62).
    * This command checks a list of points to see if any of them are on
    * the screen. This is a very powerful command: with only 8 points
    * it can be determined if the rectangular cube object is entirely
    * off the screen and does not need to be processed. This will speed
    * the scenery processing up.
    */
   virtual void IFVIS(Enum16 opcode,
                      SInt16 off_screen,
                      UInt16 count,
                      const UInt16* points);

   /** BGL_LIBRARY_CALL (0x63).
    * This is like a BGL_CALL, but it calls a library object. One
    * library object can be called from many different objects. See the
    * section on library objects for more information.
    */
   virtual void LIBRARY_CALL(Enum16 opcode,
                             UInt16 index,
                             GUid128 library_id);

   /** BGL_LIST (0x64).
    * This is used to surround several BGL commands that will be called
    * later via a BGL_SELECT command. The total_size is the size in
    * bytes of the BGL_LIST and all the BGL commands within it. The BGL
    * commands within the BGL_LIST will only be executed via a
    * BGL_SELECT command.
    */
   virtual void LIST(Enum16 opcode,
                     SInt16 total_size,
                     UInt16 count,
                     const UInt16* indexes);

   /** BGL_VSCOLOR (0x65).
    * This command gets a color out of global or local variables for
    * surfaces (polygons). The color can either be a 16-bit table color
    * or 32-bit UNICOL.
    */
   virtual void VSCOLOR(Enum16 opcode,
                        Var16 vcolor);

   /** BGL_VGCOLOR (0x66).
    * This command gets a color out of global or local variables for
    * surfaces (polygons). The color can either be a 16-bit table color
    * or 32-bit UNICOL. This is the same as VSCOLOR. Please use
    * VSCOLOR. This command will not be supported after version 7.00.
    */
   virtual void VGCOLOR(Enum16 opcode,
                        Var16 vcolor);

   /** BGL_VLCOLOR (0x67).
    * This command gets a color out of global or local variables for
    * lines. The color can either be a 16-bit table color or 32-bit
    * UNICOL.
    */
   virtual void VLCOLOR(Enum16 opcode,
                        Var16 vcolor);

   /** BGL_ROAD_START (0x69).
    * Starts a section of road. Think of this as the start of a line
    * segment. All points of the road are based of the previous scale
    * command.
    */
   virtual void ROAD_START(Enum16 opcode,
                           UInt16 width,
                           XYZ16 point);

   /** BGL_ROAD_CONT (0x6A).
    * Continue or ends a section of road. Think of this as the start of
    * a line segment. All points of the road are based on the previous
    * scale command.
    */
   virtual void ROAD_CONT(Enum16 opcode,
                          XYZ16 point);

   /** BGL_RIVER_START (0x6B).
    * Starts a section of river. Think of this as the start of a line
    * segment. All points of the river are based on the previous scale
    * command.
    */
   virtual void RIVER_START(Enum16 opcode,
                            UInt16 width,
                            XYZ16 point);

   /** BGL_RIVER_CONT (0x6C).
    * Continue or ends a section of river. Think of this as the start
    * of a line segment. All points of the river are based on the
    * previous scale command.
    */
   virtual void RIVER_CONT(Enum16 opcode,
                           XYZ16 point);

   /** BGL_IFSIZEH (0x6D).
    * This command can be used to determine how big an object is on the
    * screen. If real_size in Meters converted to horizontal pixels on
    * the screen is less than the number of pixels in pixels_ref, then
    * branch to the smaller relative address. This is the same as
    * IF_SIZEH (0x5F) except it checks the size in horizontal pixels.
    */
   virtual void IFSIZEH(Enum16 opcode,
                        SInt16 smaller,
                        UInt16 real_size,
                        UInt16 pixels_ref);

   /** BGL_TAXIWAY_START (0x6E).
    * Starts a section of taxiway. This is much the same as a road
    * except that it will be lighted with blue edge lights and
    * night. All points of the taxiway are based on the previous scale
    * command.
    */
   virtual void TAXIWAY_START(Enum16 opcode,
                              UInt16 width,
                              XYZ16 point);

   /** BGL_TAXIWAY_CONT (0x6F).
    * Continues or ends a section of taxiway. All points of the taxiway
    * are based on the previous scale command.
    */
   virtual void TAXIWAY_CONT(Enum16 opcode,
                             XYZ16 point);

   /** BGL_AREA_SENSE (0x70).
    * This is used to define a platform that an aircraft can sit on
    * above the ground. This might be a bridge, a building top, or an
    * aircraft carrier for example. These are also stackable so all the
    * floors for a building could be landable. It can also be used to
    * surround an area to set its surface type or to set weather. This
    * area is made up of XZ vertices that make up a convex polygon. The
    * XZ vertices are in scale units. This opcode will only work in the
    * miscellaneous data section of a BGL file. See the miscellaneous
    * section for examples.
    */
   virtual void AREA_SENSE(Enum16 opcode,
                           SInt16 outside,
                           UInt16 count,
                           const XZ16* point);

   /** BGL_ALTITUDE_SET (0x71).
    * This is used to set the altitude of a surface above the
    * ground. The decision as to whether the user s plane is over a
    * surface should have already been done with an AREA_SENSE,
    * IFINBOXP, or some other bounding type BGL command. More than one
    * ALTITUDE_SET can be used. To define the floors in a building, set
    * the lowest altitude first. This must be used in the miscellaneous
    * section of the BGL file.
    */
   virtual void ALTITUDE_SET(Enum16 opcode,
                             SInt16 altitude);

   /** BGL_IFINBOXP (0x73).
    * Checks to see if the user s plane is inside a rectangle,
    * referenced to the current SCALE, rotated with the current
    * INSTANCE, and in Meter units.
    */
   virtual void IFINBOXP(Enum16 opcode,
                         SInt16 outside,
                         SInt16 low_x,
                         SInt16 high_x,
                         SInt16 low_y,
                         SInt16 high_y,
                         SInt16 low_z,
                         SInt16 high_z);

   /** BGL_ADDCAT (0x74).
    * Add an object to a category list to be displayed later with
    * other objects of its type. This is primarily for ordering ground
    * objects to make sure they are displayed in the proper
    * order. Objects are ordered by categories, but it is not
    * determinate what the order is within a category. The category
    * numbers are spread out with gaps to allow expansion. The larger
    * numbered categories will be plotted after (on top) the smaller
    * numbered categories. There is a maximum of 64 categories. The
    * first command in the object should be a SCALE command and should
    * end with a BGL_RETURN.
    */
   virtual void ADDCAT(Enum16 opcode,
                       SInt16 call,
                       Enum16 category);

   /** BGL_ADDMNT (0x75).
    * Add an object to the radsort list of mountains to be displayed
    * later with other 3D objects. This is an old command that will not
    * be supported after version 7.0. Any ADDMNT object must start with
    * a SCALE command and end with a BGL_RETURN. This will not be
    * supported after version 7.00.
    */
   virtual void ADDMNT(Enum16 opcode,
                       SInt16 call);


   /** BGL_BGL (0x76).
    * This command allowed older versions of Flight Simulator to switch
    * between BGL and LOGOL. This is being phased out and should not be
    * used anymore.
    */
   virtual void BGL(Enum16 opcode);

   /** BGL_SCALE_AGL (0x77).
    * Defines a LATLONALT anchor point and design scale to use to draw
    * objects. This command automatically sets the altitude to be the
    * ground at its specific LATLON. Except for this it is exactly the
    * same as the SCALE (0x2F) command. The reason for using this is
    * that the ground can move up and down depending on what terrain is
    * below. Special note: the altitude portion of lla must be 0.
    */
   virtual void SCALE_AGL(Enum16 opcode,
                          SInt16 fail,
                          UInt16 range,
                          UInt16 size,
                          Var16 index,
                          UInt32 scale,
                          LLA lla);

   /** BGL_ROAD_CONTW (0x78).
    * Continues or ends a section of road and can change the road s
    * width. This is the same as ROAD_CONT (0x6A) except it contains a
    * new width. All points of the road are based of the previous scale
    * command.
    */
   virtual void ROAD_CONTW(Enum16 opcode,
                           UInt16 width,
                           XYZ16 point);



   /** BGL_RIVER_CONTW (0x79).
    * Continues or ends a section of river and can change the river s
    * width. This is the same as RIVER_CONT (0x6C) except it contains a
    * new width. All points of the river are based on the previous
    * scale command.
    */
   virtual void RIVER_CONTW(Enum16 opcode,
                            UInt16 width,
                            XYZ16 point);

   /** BGL_GFACET_TMAP (0x7A).
    * Gouraud Textured surface (polygon) with a normal and reference
    * value for backface culling. This is handled exactly the same as
    * FACET_TMAP (x20). Each vertex on the polygon also has a texture
    * coordinate associated with it. This is a convex polygon unless it
    * is preceded by a CONCAVE command.
    */
   virtual void GFACET_TMAP(Enum16 opcode,
                            UInt16 count,
                            XYZ16 normal,
                            SInt32 dot_ref,
                            const PXZ16* vertices);


   /** BGL_SELECT (0x7C).
    * Selects and executes a BGL command out of a BGL_LIST. A BGL
    * command can be selected out of a list with a variable or a
    * constant.
    */
   virtual void SELECT(Enum16 opcode,
                       SInt16 vindex,
                       UInt16 shift_mask,
                       SInt32 list);

   /** BGL_PERSPECTIVE (0x7D).
    * Makes the next textured facet (surface, polygon) perspective
    * corrected during its display. All facets are always perspective
    * corrected now, so this command is not used. It is now obsolete so
    * please discontinue using it. DO NOT USE.
    */
   virtual void PERSPECTIVE(Enum16 opcode);

   /** BGL_SETWRD_GLOBAL (0x7E).
    * Sets the value of a global variable. This is always a 16-bit
    * variable. There are a limited number of global variables that
    * should be written. Make sure that others are not written.
    */
   virtual void SETWRD_GLOBAL(Enum16 opcode,
                              Enum16 gindex,
                              SInt16 value);



   /** BGL_RESPNT (0x80).
    * Draw a point (light) at a point defined in the vertex/point list.
    */
   virtual void RESPNT(Enum16 opcode,
                       Enum16 pindex);

   /** BGL_RESCALE (0x83).
    * Refines the scale of a previous set LATLONALT anchor point and
    * design scale to use to draw objects. This can be used if the eye
    * is too far away from a scale command and it overflowed to define
    * the scale in larger units.
    */
   virtual void RESCALE(Enum16 opcode,
                        SInt16 fail,
                        UInt16 range,
                        UInt16 size,
                        UInt32 scale);

   /** BGL_FIXED_COLORS (0x87).
    * Defines the number of colors at the end of a palette that are not
    * changed with the time of day. This allows for colors in textures
    * to not change with night. This is an old way of bright colors and
    * will not be supported after version 7.00. So it is now obsolete.
    */
   virtual void FIXED_COLORS(Enum16 opcode,
                             UInt16 count);

   /** BGL_JUMP32 (0x88).
    * Unconditionally continues processing at new address in the
    * current BGL object. CANNOT JUMP across different objects. Same as
    * a JUMP except that it has a 32-bit relative offset.
    */
   virtual void JUMP32(Enum16 opcode,
                       SInt32 jump);

   /** BGL_Var_BASE32 (0x89).
    * This allows access to local variables or parameter
    * variables. There are special ranges and numbers for the address
    * argument.
    */
   virtual void Var_BASE32(Enum16 opcode,
                           Var32 address);

   /** BGL_CALL32 (0x8A).
    * Unconditionally continues start processing at a new address by
    * nesting in the current BGL object. BGL_RETURN from the subroutine
    * will continue processing at the next command. CANNOT CALL across
    * different objects. This is the same as a CALL except it has a
    * 32-bit relative offset.
    */
   virtual void CALL32(Enum16 opcode,
                       SInt32 call);

   /** BGL_ADDCAT32 (0x8B)
    * Adds an object to a category list to be displayed later with
    * other objects of its type. This is primarily for ordering ground
    * objects to make sure they are displayed in the proper
    * order. Objects are ordered by categories, but it is not
    * determinate what the order is within a category. The category
    * numbers are spread out with gaps to allow expansion. The larger
    * numbered categories will be plotted after (on top) the smaller
    * numbered categories. There is a maximum of 64 categories. The
    * first command in the object should be a SCALE command and should
    * end with a RETURN. This is the same as an ADDCAT except it has a
    * 32-bit relative offset.
    */
   virtual void ADDCAT32(Enum16 opcode,
                         SInt32 call,
                         Enum16 category);

   /** BGL_VFILE_MARKER (0x8E).
    * file marker command for aircraft.
    */
   virtual void VFILE_MARKER(Enum16 opcode,
                             SInt16 offset);

   /** BGL_ALPHA (0x8F).
    * this command sets the global alpha blend flag. Alpha blending
    * stays in effect until an ALPHA 0 command turns it off. If
    * texturing, and an alpha value is supplied in the range 1->255,
    * then this alpha value is used as-is. If the alpha value is
    * outside this range, then an alpha value of 255 is used. If not
    * texturing, then whatever alpha value is supplied in SCOLOR (via
    * appropriate UNICOL mapping). Note: non-facets (i.e., lines) are
    * never alpha blended.
    */
   virtual void ALPHA(Enum16 opcode,
                      UInt32 value);


   /** BGL_TEXT (0x91).
    * Plots a text string on the screen.
    */
   virtual void BTEXT(Enum16 opcode,
                      XYZ16 start_point,
                      Var16 vtext,
                      Flags16 flags);

   /** BGL_CRASH (0x94).
    * contains the information about an object needed for the crash
    * detection code. This command should be in custom objects before
    * the ADDOBJ. This should not be used in a library object.
    */
   virtual void CRASH(Enum16 opcode,
                      UInt16 length,
                      UInt16 ground_radius,
                      SInt16 scale,
                      SInt16 instance,
                      Bool8 processed,
                      Enum8 density);

   /** BGL_CRASH_INDIRECT (0x95).
    * contains the information about an object needed for the crash
    * detection code. This command should be in inline BGL code that
    * calls other BGL code in the same object or a library. This should
    * not be used in a library object itself.
    */
   virtual void CRASH_INDIRECT(Enum16 opcode,
                               SInt16 call,
                               SInt16 scale,
                               SInt16 instance,
                               Bool8 processed,
                               Enum8 density);

   /** BGL_CRASH_START (0x96).
    * this starts the crash code inside of a called object or library
    * object.
    */
   virtual void CRASH_START(Enum16 opcode,
                            UInt16 length,
                            UInt16 ground_radius);

   /** BGL_CRASH_SPHERE (0x97).
    * Checks to see if the user s aircraft is inside a sphere with its
    * center at the scale point. It is always best to use the sphere
    * test first because it is by far the fastest check.
    */
   virtual void CRASH_SPHERE(Enum16 opcode,
                             SInt16 outside,
                             UInt16 radius);

   /** BGL_CRASH_BOX (0x98).
    * Checks to see if the user s aircraft is inside a rotated
    * rectangle.
    */
   virtual void CRASH_BOX(Enum16 opcode,
                          SInt16 outside,
                          XYZ16 center_bias,
                          XYZ16 rectangle,
                          PBH16 pbh);

   /** BGL_SET_CRASH (0x99).
    * If through all the positioning and bounds checking it is
    * determined that the aircraft has crashed into an object, this is
    * the BGL command to report that crash.
    */
   virtual void SET_CRASH(Enum16 opcode,
                          Enum16 type);

   /** BGL_ INTERPOLATE (0x9E).
    * Through points defined in a table, this command will interpolate
    * an input value into an output value. Please see Var_BASE_32
    * (0x89) for information of the variables bases.
    */
   virtual void INTERPOLATE(Enum16 opcode,
                            SInt32 vinput_base,
                            SInt16 vinput,
                            SInt32 voutput_base,
                            SInt16 voutput,
                            SInt32 vtable_base,
                            SInt16 vinput2);

   /** BGL_ OVERRIDE (0x9F).
    * This is exactly the same as the VAS_BASE_32 except that it is
    * only in effect for the next command that accesses a
    * variable. After the next command that references variables, the
    * var_base will be returned to what it was before this command.
    */
   virtual void OVERRIDE(Enum16 opcode,
                         SInt32 vbase);

   /** BGL_OBJECT (0xA0).
    * This command replaces the old BUILDING command. It is more
    * verbose and expandable. It is assumed that a SCALE command and
    * INSTANCE rotation is already done. Currently the only objects are
    * buildings. These buildings are divided up into 3 sections: bottom
    * or store front/entrance, middle or window section which is
    * usually repeated, and top (trim) section just below the
    * roof. Each object consists of a header and the object s unique
    * data. Each of these objects is internally generated inside Flight
    * Simulator.
    */

   virtual void BUILD_RECT_FLAT_ROOF(Enum16 opcode,
                                     UInt16 total_length,
                                     Enum16 category,
                                     const BUILD_RECT_FLAT_ROOF_S& build);

   virtual void BUILD_RECT_RIDGE_ROOF(Enum16 opcode,
                                      UInt16 total_length,
                                      Enum16 category,
                                      const BUILD_RECT_RIDGE_ROOF_S& build);

   virtual void BUILD_RECT_PEAK_ROOF(Enum16 opcode,
                                     UInt16 total_length,
                                     Enum16 category,
                                     const BUILD_RECT_PEAK_ROOF_S& build);

   virtual void BUILD_RECT_SLANT_ROOF(Enum16 opcode,
                                      UInt16 total_length,
                                      Enum16 category,
                                      const BUILD_RECT_SLANT_ROOF_S& build);

   virtual void BUILD_PYRAMID(Enum16 opcode,
                              UInt16 total_length,
                              Enum16 category,
                              const BUILD_PYRAMID_S& build);

   virtual void BUILD_MULTI_SIDED(Enum16 opcode,
                                  UInt16 total_length,
                                  Enum16 category,
                                  const BUILD_MULTI_SIDED_S& build);

   /** BGL_VALPHA (0xA4).
    * this command sets the global alpha blend flag. Alpha blending
    * stays in effect until an ALPHA 0 (or VALPHA with a variable value
    * of 0) command turns it off. This is the same as ALPHA except that
    * it is indirect through a variable. If texturing, and an alpha
    * value is supplied in the range 1->255, then this alpha value is
    * used as is. If the alpha value is outside this range, then an
    * alpha value of 255 is used. If not texturing, then whatever alpha
    * value is supplied in SCOLOR (via appropriate UNICOL
    * mapping). Note: non-facets (i.e., lines) are never alpha blended.
    */
   virtual void VALPHA(Enum16 opcode,
                       SInt16 variable);

   /** BGL_SPRITE_VICALL (0xA7).
    * This command is similar to a POINT_VI_CALL but the object is
    * always rotated toward the eye. It can be rotated in pitch, bank,
    * or heading. Each of these will be rotated if the fixed rotation
    * is non-zero. The fixed rotation and variable rotation is added
    * after the object is rotated toward the eye.
    */
   virtual void SPRITE_VICALL(Enum16 opcode,
                              SInt16 call,
                              XYZ16 offset,
                              PBH16 pbh,
                              SInt16 vpitch,
                              SInt16 vbank,
                              SInt16 vheading);

   /** BGL_TEXTURE_ROAD_START (0xA8).
    * This is a new type of road, river, railroad, & command that draws
    * these segmented line type objects over the terrain. Think of this
    * as the start of a line segment. All points of the road are based
    * on the previous scale command. This can be followed by the other
    * type of road or river continue commands.
    */
   virtual void TEXTURE_ROAD_START(Enum16 opcode,
                                   Enum16 style,
                                   UInt16 width,
                                   XYZ16 point);

   /** BGL_IFIN_INSTANCED_BOX_PLANE (0xA9).
    * If the user s plane is inside this rectangle, fall through to the
    * next command. This box is already rotated with instance type
    * commands for the object.
    */
   virtual void IFIN_INSTANCED_BOX_PLANE(Enum16 opcode,
                                         SInt16 fail,
                                         XYZ16 center,
                                         XYZ16 size,
                                         PBH16 rotation);

   /** BGL_NEW_RUNWAY (0xAA).
    * This is a new style of runway command and system added in Flight
    * Simulator 7.00. It is made up of a base command opcode with many
    * self-contained opcodes within it. This allows for maximum
    * efficiency as well as expansion at any time. The efficiency comes
    * from only having the data needed for a particular runway. Simple
    * runways are small and complex runways are large. It is expandable
    * at any time through the addition of another sub-opcode. Please
    * use this instead of the old runway commands. The sub-opcodes can
    * be in any order with the exception that RUNWAY_SUBOP_BASE (0x01)
    * must be first. Do not include sub-opcodes if they are not needed.
    */
   virtual void NEW_RUNWAY(Enum16 opcode,
                           UInt16 total_length);

   /** RUNWAY_BASE (0x01).
    * This is the base information about the runway that each must
    * contain and must be the first sub-opcode:
    */
   virtual void RWY_RUNWAY_BASE(Enum8 sub_opcode,
                                LLA lla,
                                Angl16 heading,
                                UInt16 length,
                                UInt16 width,
                                Flags16 markings,
                                Enum8 surface_type,
                                Flags8 surface_lights,
                                Flags8	identifiers);

   /** BASE_THRESHOLD (0x02).
    * for a base offset threshold (this length is included in the
    * length of the runway)
    */
   virtual void RWY_BASE_THRESHOLD(Enum8 sub_opcode,
                                   UInt8 spare,
                                   UInt16 length);

   /** RECIP_THRESHOLD (0x03).
    * for a reciprocal offset threshold (this length is included in the
    * length of the runway)
    */
   virtual void RWY_RECIP_THRESHOLD(Enum8 sub_opcode,
                                    UInt8 spare,
                                    UInt16 length);

   virtual void RWY_BASE_BLAST_PAD(Enum8 sub_opcode,
                                   UInt8 spare,
                                   UInt16 length);

   virtual void RWY_RECIP_BLAST_PAD(Enum8 sub_opcode,
                                    UInt8 spare,
                                    UInt16 length);


   virtual void RWY_BASE_APPROACH_LIGHTS(Enum8 sub_opcode,
                                         UInt8 spare,
                                         Flags8 flags,
                                         Enum8 system,
                                         Enum8 strobes,
                                         Flags8 vasi_system,
                                         Angl16 vasi_angle,
                                         SInt16 vasi_x,
                                         SInt16 vasi_z,
                                         SInt16 vasi_spacing);

   virtual void RWY_RECIP_APPROACH_LIGHTS(Enum8 sub_opcode,
                                          UInt8 spare,
                                          Flags8 flags,
                                          Enum8 system,
                                          Enum8 strobes,
                                          Flags8 vasi_system,
                                          Angl16 vasi_angle,
                                          SInt16 vasi_x,
                                          SInt16 vasi_z,
                                          SInt16 vasi_spacing);

   virtual void RWY_BASE_OVERRUN(Enum8 sub_opcode,
                                 Enum8 surface_type,
                                 UInt16 length);

   virtual void RWY_RECIP_OVERRUN(Enum8 sub_opcode,
                                  Enum8 surface_type,
                                  UInt16 length);

   virtual void RWY_BASE_DISTANCE_LEFT(Enum8 sub_opcode,
                                       UInt8 info,
                                       UInt16 x_offset);

   virtual void RWY_RECIP_DISTANCE_LEFT(Enum8 sub_opcode,
                                        UInt8 info,
                                        UInt16 x_offset);

   /** BGL_ZBIAS (0xAC).
    * This will bias (add to) the Z distance an object is away from the
    * eye so that co-planer object will draw in the correct order. This
    * should be used very carefully with small numbers. Should be a
    * value 0-15.
    */
   virtual void ZBIAS(Enum16 opcode,
                      UInt16 zbias);

   /** BGL_ANIMATE (0xAD).
    * Through a key frame table this will animate rotate a part(s) of
    * an object. The rotation MUST be ended by TRANSFORM_END (0xAE)
    */
   virtual void ANIMATE(Enum16 opcode,
                        SInt32 vinput_base,
                        SInt32 vinput,
                        SInt32 vtable_base,
                        SInt32 vtable,
                        Float32 x, Float32 y, Float32 z);

   /** BGL_ TRANSFORM_END (0xAE).
    * This command ends an animation rotation.
    */
   virtual void TRANSFORM_END(Enum16 opcode);

   /** BGL_TRANSFORM_MATRIX (0xAD).
    * This command sets a new 4x3 transform (3x3 matrix +
    * translate). The transform MUST be ended by a TRANSFORM_END
    * (0xAE).
    */
   virtual void TRANSFORM_MATRIX(Enum16 opcode,
                                 XYZF32 values,
                                 Float32 q00,
                                 Float32 q01,
                                 Float32 q02,

                                 Float32 q10,
                                 Float32 q11,
                                 Float32 q12,

                                 Float32 q20,
                                 Float32 q21,
                                 Float32 q22);


   /** BGL_ LIGHT (0xB2).
    * This produces visuals for lights. The LIGHT_BEACON, LIGHT_NAV,
    * and LIGHT_STROBE types generate a point light and use the
    * location, intensity, and color parameters. The LIGHT_TAXI and
    * LIGHT_LANDING types generate a cone along the Z axis of the
    * previous scale command and use the color parameter.
    */
   virtual void LIGHT(Enum16 opcode,
                      Enum16 light_type,
                      XYZF32 location,
                      UInt32 intensity,
                      Float32 reserved1,
                      Float32 reserved2,
                      UNICOL color,
                      XYZF32 reserved3);

   /** BGL_IFINF1 (0xB3).
    * Checks whether a specified variable is within specific bounds. If
    * low <= var <= high. This is the floating point version of IFIN1
    *
    * \bug According to the spec the fail offset should be 16-bits, but 32-bits
    * seems more likely.
    */
   virtual void IFINF1(Enum16  opcode,
                       SInt32  fail,
                       Var16   var,
                       Float32 low,
                       Float32 high);
   /*
   virtual void IFINF1(Enum16  opcode,
                       SInt16  fail,
                       Var16   var,
                       Float32 low,
                       Float32 high);
   */

   /** BGL_TEXTURE_SIZE (0xB4).
    * Tells the graphics system the size of a texture in meters. The
    * texture size is used to select the correct mip- level. This
    * command is only used to change the texture size, the base texture
    * size is stored in the current texture list.
    */
   virtual void TEXTURE_SIZE(Enum16 opcode,
                             Float32 size);

   /** BGL_VERTEX_LIST (0xB5).
    * Provides a list of 3-D vertexes with which to draw a 3-D object.
    */
   virtual void VERTEX_LIST(Enum16 opcode,
                            UInt16 count,
                            UInt32 reserved,
                            const VERTEX* vertex);

   /** BGL_MATERIAL_LIST (0xB6).
    * Provides a list of materials to use in displaying a 3-D object.
    */
   virtual void MATERIAL_LIST(Enum16 opcode,
                              UInt16 count,
                              UInt32 reserved,
                              const MATERIAL* material);

   /** BGL_TEXTURE_LIST (0xB7).
    * Provides a list textures to use in displaying a 3D object.
    */
   virtual void TEXTURE_LIST(Enum16 opcode,
                             UInt16 count,
                             UInt32 reserved,
                             const TEXTURE* texture);

   /** BGL_SET_MATERIAL (0xB8).
    * Selects the current material and texture to use to draw 3-D polygons.
    *
    * <h3> Notes</h3>
    * <ul>
    * <li> Indices are zero based.
    * <li> A texture index of 0FFFFh means no texture.
    * <li> If the selected texture is not loaded the material diffuse color is used as the fallback.
    * <li> If the material diffuse color has alpha (diffuse.a != 1.0) alpha blending is enabled.
    * </ul>
    */
   virtual void SET_MATERIAL(Enum16 opcode,
                             UInt16 material_index,
                             UInt16 texture_index);

   /** BGL_DRAW_TRIAnglE_LIST (0xB9).
    * Provides a list of vextexes to draw triangles in conjunction with the previous commands.
    */
   virtual void DRAW_TRIAnglE_LIST(Enum16 opcode,
                                   UInt16 vertext_start,
                                   UInt16 vertex_count,
                                   UInt16 index_count,
                                   const UInt16* index_list);

   /** BGL_DRAW_LINE_LIST (0xBA).
    * Provides a list of line vertexes to draw lines in conjunction with the previous commands
    */
   virtual void DRAW_LINE_LIST(Enum16 opcode,
                               UInt16 vertext_start,
                               UInt16 vertex_count,
                               UInt16 index_count,
                               const UInt16* index_list);

   /** BGL_DRAW_POINT_LIST (0xBB).
    * Provides a list of vertexes to draw points in conjunction with
    * the previous commands. Note: This opcode does not function
    * correctly in CFS2 and FS2002; therefore, do not use it. U se the
    * older opcode BGL_POINT to draw points in CFS2 and FS2002.
    */
   virtual void DRAW_POINT_LIST(Enum16 opcode,
                                UInt16 vertext_start,
                                UInt16 vertex_count,
                                UInt16 index_count,
                                const UInt16* index_list);


   /** BGL_BEGIN (0xBC).
    * Sets the version of BGL for which this code was designed. All BGL
    * instructions between BGL_BEGIN and BGL_END are assumed to be
    * designed for the specified version.
    */
   virtual void BEGIN(Enum16 opcode,
                      UInt32 version);

   /** BGL_END (0xBD).
    * Marks the end of BGL code designed for a specific version. Must
    * match a previous BGL_BEGIN.
    */
   virtual void END(Enum16 opcode);

};
}
}

#endif // BGLPARSER_H
