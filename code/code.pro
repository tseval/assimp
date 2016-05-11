
TEMPLATE = lib
TARGET = assimp
INCLUDEPATH += . BoostWorkaround ../contrib/zlib ../include
CONFIG += staticlib

CONFIG += c++11

#DEFINES += ASSIMP_BUILD_DLL_EXPORT
DEFINES += ASSIMP_BUILD_BOOST_WORKAROUND
PRECOMPILED_HEADER = AssimpPCH.h

win32 {
   DEFINES += _SCL_SECURE_NO_WARNINGS
   DEFINES += _CRT_SECURE_NO_WARNINGS
}

win32 {
   DESTDIR = $$shadowed($$PWD/../)
}

CONFIG(debug, debug|release) {
#   message(Bulding DEBUG version)
   DBG_EXT=d
   TARGET = $$join(TARGET,,,$$DBG_EXT)
}

ARCH_EXT=32
#contains(QMAKE_TARGET.arch, x86_64) {
#   ARCH_EXT=64
##   TARGET = $$join(TARGET,,,$$ARCH_EXT)
#}

# This is apparently better supported than QMAKE_TARGET.arch
# https://bugreports.qt.io/browse/QTBUG-30263
contains(QT_ARCH, x86_64) {
   ARCH_EXT=64
}

target.path = ../lib$${ARCH_EXT}
INSTALLS += target

# Input
HEADERS += 3DSHelper.h \
           3DSLoader.h \
           ACLoader.h \
           ASELoader.h \
           ASEParser.h \
           assbin_chunks.h \
           AssimpPCH.h \
           B3DImporter.h \
           BaseImporter.h \
           BaseProcess.h \
           BGL.h \
           BGLParser.h \
           BlenderBMesh.h \
           BlenderDNA.h \
           BlenderIntermediate.h \
           BlenderLoader.h \
           BlenderModifier.h \
           BlenderScene.h \
           BlenderSceneGen.h \
           BlenderTessellator.h \
           BlobIOSystem.h \
           BVHLoader.h \
           ByteSwap.h \
           CalcTangentsProcess.h \
           CInterfaceIOWrapper.h \
           COBLoader.h \
           COBScene.h \
           ColladaExporter.h \
           ColladaHelper.h \
           ColladaLoader.h \
           ColladaParser.h \
           ComputeUVMappingProcess.h \
           ConvertToLHProcess.h \
           CSMLoader.h \
           DeboneProcess.h \
           DefaultIOStream.h \
           DefaultIOSystem.h \
           DefaultProgressHandler.h \
           DXFHelper.h \
           DXFLoader.h \
           Exceptional.h \
           fast_atof.h \
           FBXCompileConfig.h \
           FBXConverter.h \
           FBXDocument.h \
           FBXDocumentUtil.h \
           FBXImporter.h \
           FBXImportSettings.h \
           FBXParser.h \
           FBXProperties.h \
           FBXTokenizer.h \
           FBXUtil.h \
           FileLogStream.h \
           FileSystemFilter.h \
           FindDegenerates.h \
           FindInstancesProcess.h \
           FindInvalidDataProcess.h \
           FixNormalsStep.h \
           GenericProperty.h \
           GenFaceNormalsProcess.h \
           GenVertexNormalsProcess.h \
           HalfLifeFileData.h \
           Hash.h \
           HMPFileData.h \
           HMPLoader.h \
           IFCLoader.h \
           IFCReaderGen.h \
           IFCUtil.h \
           IFF.h \
           Importer.h \
           ImproveCacheLocality.h \
           IRRLoader.h \
           IRRMeshLoader.h \
           IRRShared.h \
           irrXMLWrapper.h \
           JoinVerticesProcess.h \
           LimitBoneWeightsProcess.h \
           LineSplitter.h \
           LogAux.h \
           LWOAnimation.h \
           LWOFileData.h \
           LWOLoader.h \
           LWSLoader.h \
           MakeVerboseFormat.h \
           MaterialSystem.h \
           MD2FileData.h \
           MD2Loader.h \
           MD2NormalTable.h \
           MD3FileData.h \
           MD3Loader.h \
           MD4FileData.h \
           MD5Loader.h \
           MD5Parser.h \
           MDCFileData.h \
           MDCLoader.h \
           MDCNormalTable.h \
           MDLDefaultColorMap.h \
           MDLFileData.h \
           MDLLoader.h \
           MemoryIOWrapper.h \
           MS3DLoader.h \
           MSFSFileData.h \
           MSFSLoader.h \
           MSFSMDL2Parser.h \
           NDOLoader.h \
           NFFLoader.h \
           ObjExporter.h \
           ObjFileData.h \
           ObjFileImporter.h \
           ObjFileMtlImporter.h \
           ObjFileParser.h \
           ObjTools.h \
           OFFLoader.h \
           OgreImporter.hpp \
           OgreXmlHelper.hpp \
           OptimizeGraph.h \
           OptimizeMeshes.h \
           ParsingUtils.h \
           PlyExporter.h \
           PlyLoader.h \
           PlyParser.h \
           PolyTools.h \
           PretransformVertices.h \
           ProcessHelper.h \
           Profiler.h \
           pstdint.h \
           Q3BSPFileData.h \
           Q3BSPFileImporter.h \
           Q3BSPFileParser.h \
           Q3BSPZipArchive.h \
           Q3DLoader.h \
           qnan.h \
           RawLoader.h \
           RemoveComments.h \
           RemoveRedundantMaterials.h \
           RemoveVCProcess.h \
           SceneCombiner.h \
           ScenePreprocessor.h \
           ScenePrivate.h \
           SGSpatialSort.h \
           SkeletonMeshBuilder.h \
           SMDLoader.h \
           SmoothingGroups.h \
           SortByPTypeProcess.h \
           SpatialSort.h \
           SplitByBoneCountProcess.h \
           SplitLargeMeshes.h \
           StandardShapes.h \
           StdOStreamLogStream.h \
           STEPFile.h \
           STEPFileEncoding.h \
           STEPFileReader.h \
           STLExporter.h \
           STLLoader.h \
           StreamReader.h \
           StringComparison.h \
           Subdivision.h \
           TargetAnimation.h \
           TerragenLoader.h \
           TextureTransform.h \
           TinyFormatter.h \
           TriangulateProcess.h \
           UnrealLoader.h \
           ValidateDataStructure.h \
           Vertex.h \
           VertexTriangleAdjacency.h \
           Win32DebugLogStream.h \
           XFileHelper.h \
           XFileImporter.h \
           XFileParser.h \
           XGLLoader.h \
           res/resource.h \
           BoostWorkaround/boost/foreach.hpp \
           BoostWorkaround/boost/format.hpp \
           BoostWorkaround/boost/lexical_cast.hpp \
           BoostWorkaround/boost/make_shared.hpp \
           BoostWorkaround/boost/noncopyable.hpp \
           BoostWorkaround/boost/pointer_cast.hpp \
           BoostWorkaround/boost/scoped_array.hpp \
           BoostWorkaround/boost/scoped_ptr.hpp \
           BoostWorkaround/boost/shared_array.hpp \
           BoostWorkaround/boost/shared_ptr.hpp \
           BoostWorkaround/boost/static_assert.hpp \
           BoostWorkaround/boost/timer.hpp \
           BoostWorkaround/boost/math/common_factor_rt.hpp \
           BoostWorkaround/boost/tuple/tuple.hpp \
           ../include/assimp/defs.h \
           ../include/assimp/DefaultLogger.hpp \
           ../include/assimp/Logger.hpp \
           ../include/assimp/types.h \
           ../include/assimp/vector3.h \
           ../include/assimp/Compiler/pushpack1.h \
           ../include/assimp/Compiler/poppack1.h \
           ../include/assimp/vector2.h \
           ../include/assimp/color4.h \
           ../include/assimp/matrix3x3.h \
           ../include/assimp/matrix4x4.h \
           ../include/assimp/quaternion.h \
           ../include/assimp/vector2.inl \
           ../include/assimp/vector3.inl \
           ../include/assimp/color4.inl \
           ../include/assimp/quaternion.inl \
           ../include/assimp/matrix3x3.inl \
           ../include/assimp/matrix4x4.inl \
           ../include/assimp/LogStream.hpp \
           ../include/assimp/NullLogger.hpp \
           ../include/assimp/IOStream.hpp \
           ../include/assimp/IOSystem.hpp \
           ../include/assimp/scene.h \
           ../include/assimp/texture.h \
           ../include/assimp/mesh.h \
           ../include/assimp/light.h \
           ../include/assimp/camera.h \
           ../include/assimp/material.h \
           ../include/assimp/material.inl \
           ../include/assimp/anim.h \
           ../include/assimp/metadata.h \
           ../include/assimp/importerdesc.h \
           ../include/assimp/postprocess.h \
           ../include/assimp/Importer.hpp \
           ../include/assimp/config.h \
           ../include/assimp/Exporter.hpp \
           ../include/assimp/cexport.h \
           ../include/assimp/ai_assert.h \
           SmoothingGroups.inl \
           ../include/assimp/cimport.h \
           ../include/assimp/cfileio.h \
           ../include/assimp/version.h \
           ../revision.h \
           ../contrib/ConvertUTF/ConvertUTF.h \
           BlenderDNA.inl \
           ../contrib/poly2tri/poly2tri/poly2tri.h \
           ../contrib/poly2tri/poly2tri/common/shapes.h \
           ../contrib/poly2tri/poly2tri/sweep/cdt.h \
           ../contrib/poly2tri/poly2tri/sweep/advancing_front.h \
           ../contrib/poly2tri/poly2tri/sweep/sweep_context.h \
           ../contrib/poly2tri/poly2tri/sweep/sweep.h \
           ../contrib/zlib/zlib.h \
           ../contrib/irrXML/irrXML.h \
           ../contrib/clipper/clipper.hpp \
           ../contrib/unzip/unzip.h \
           ../contrib/unzip/ioapi.h \
           ../include/assimp/ProgressHandler.hpp
SOURCES += 3DSConverter.cpp \
           3DSLoader.cpp \
           ACLoader.cpp \
           ASELoader.cpp \
           ASEParser.cpp \
           Assimp.cpp \
           AssimpCExport.cpp \
           AssimpPCH.cpp \
           B3DImporter.cpp \
           BaseImporter.cpp \
           BaseProcess.cpp \
           BGLParser.cpp \
           BlenderBMesh.cpp \
           BlenderDNA.cpp \
           BlenderLoader.cpp \
           BlenderModifier.cpp \
           BlenderScene.cpp \
           BlenderTessellator.cpp \
           BVHLoader.cpp \
           CalcTangentsProcess.cpp \
           COBLoader.cpp \
           ColladaExporter.cpp \
           ColladaLoader.cpp \
           ColladaParser.cpp \
           ComputeUVMappingProcess.cpp \
           ConvertToLHProcess.cpp \
           CSMLoader.cpp \
           DeboneProcess.cpp \
           DefaultIOStream.cpp \
           DefaultIOSystem.cpp \
           DefaultLogger.cpp \
           DXFLoader.cpp \
           Exporter.cpp \
           FBXAnimation.cpp \
           FBXBinaryTokenizer.cpp \
           FBXConverter.cpp \
           FBXDeformer.cpp \
           FBXDocument.cpp \
           FBXDocumentUtil.cpp \
           FBXImporter.cpp \
           FBXMaterial.cpp \
           FBXMeshGeometry.cpp \
           FBXModel.cpp \
           FBXNodeAttribute.cpp \
           FBXParser.cpp \
           FBXProperties.cpp \
           FBXTokenizer.cpp \
           FBXUtil.cpp \
           FindDegenerates.cpp \
           FindInstancesProcess.cpp \
           FindInvalidDataProcess.cpp \
           FixNormalsStep.cpp \
           GenFaceNormalsProcess.cpp \
           GenVertexNormalsProcess.cpp \
           HMPLoader.cpp \
           IFCBoolean.cpp \
           IFCCurve.cpp \
           IFCGeometry.cpp \
           IFCLoader.cpp \
           IFCMaterial.cpp \
           IFCOpenings.cpp \
           IFCProfile.cpp \
           IFCReaderGen.cpp \
           IFCUtil.cpp \
           Importer.cpp \
           ImporterRegistry.cpp \
           ImproveCacheLocality.cpp \
           IRRLoader.cpp \
           IRRMeshLoader.cpp \
           IRRShared.cpp \
           JoinVerticesProcess.cpp \
           LimitBoneWeightsProcess.cpp \
           LWOAnimation.cpp \
           LWOBLoader.cpp \
           LWOLoader.cpp \
           LWOMaterial.cpp \
           LWSLoader.cpp \
           MakeVerboseFormat.cpp \
           MaterialSystem.cpp \
           MD2Loader.cpp \
           MD3Loader.cpp \
           MD5Loader.cpp \
           MD5Parser.cpp \
           MDCLoader.cpp \
           MDLLoader.cpp \
           MDLMaterialLoader.cpp \
           MS3DLoader.cpp \
           MSFSLoader.cpp \
           MSFSMDL2Parser.cpp \
           NDOLoader.cpp \
           NFFLoader.cpp \
           ObjExporter.cpp \
           ObjFileImporter.cpp \
           ObjFileMtlImporter.cpp \
           ObjFileParser.cpp \
           OFFLoader.cpp \
           OgreImporter.cpp \
           OgreMaterial.cpp \
           OgreMesh.cpp \
           OgreSkeleton.cpp \
           OptimizeGraph.cpp \
           OptimizeMeshes.cpp \
           PlyExporter.cpp \
           PlyLoader.cpp \
           PlyParser.cpp \
           PostStepRegistry.cpp \
           PretransformVertices.cpp \
           ProcessHelper.cpp \
           Q3BSPFileImporter.cpp \
           Q3BSPFileParser.cpp \
           Q3BSPZipArchive.cpp \
           Q3DLoader.cpp \
           RawLoader.cpp \
           RemoveComments.cpp \
           RemoveRedundantMaterials.cpp \
           RemoveVCProcess.cpp \
           SceneCombiner.cpp \
           ScenePreprocessor.cpp \
           SGSpatialSort.cpp \
           SkeletonMeshBuilder.cpp \
           SMDLoader.cpp \
           SortByPTypeProcess.cpp \
           SpatialSort.cpp \
           SplitByBoneCountProcess.cpp \
           SplitLargeMeshes.cpp \
           StandardShapes.cpp \
           STEPFileEncoding.cpp \
           STEPFileReader.cpp \
           STLExporter.cpp \
           STLLoader.cpp \
           Subdivision.cpp \
           TargetAnimation.cpp \
           TerragenLoader.cpp \
           TextureTransform.cpp \
           TriangulateProcess.cpp \
           UnrealLoader.cpp \
           ValidateDataStructure.cpp \
           VertexTriangleAdjacency.cpp \
           XFileImporter.cpp \
           XFileParser.cpp \
           XGLLoader.cpp \
           ../contrib/ConvertUTF/ConvertUTF.c \
           ../contrib/unzip/ioapi.c \
           ../contrib/unzip/unzip.c \
           ../contrib/poly2tri/poly2tri/common/shapes.cc \
           ../contrib/poly2tri/poly2tri/sweep/cdt.cc \
           ../contrib/poly2tri/poly2tri/sweep/advancing_front.cc \
           ../contrib/poly2tri/poly2tri/sweep/sweep_context.cc \
           ../contrib/poly2tri/poly2tri/sweep/sweep.cc \
           ../contrib/irrXML/irrXML.cpp \
           ../contrib/clipper/clipper.cpp