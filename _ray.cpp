
#include "RendererFactory.cpp"
#include "SceneBase.cpp"

#include "internal/BVHSplit.cpp"
#include "internal/TextureSplitter.cpp"

#include "internal/Core.cpp"

#include "internal/CoreRef.cpp"
#include "internal/FramebufferRef.cpp"
#include "internal/RendererRef.cpp"
#include "internal/SceneRef.cpp"
#include "internal/TextureAtlasRef.cpp"
#include "internal/TextureUtilsRef.cpp"

#if defined(__ARM_NEON__) || defined(__aarch64__)
#include "internal/RendererNEON.cpp"
#endif

#if defined(__ANDROID__) || defined(DISABLE_OCL)
#else
#include "internal/RendererOCL.cpp"
#include "internal/SceneOCL.cpp"
#include "internal/TextureAtlasOCL.cpp"
#endif

// TODO:
// replace box filter with tent
// compare traversal algorithm with stack
// try using image for node buffer (utilize texture cache)
// add punctual lights support
// add deletion functions for OpenCL backend
// add tests for intersection
// add more validation tests (use Cycles)

// DONE:
// add dof
// try again with spatial splits or remove unnecessary indirection
// proper ray termination
// add validation tests (use Cycles)
// make camera fov work
// add neon support
// add android build
// add shading to cpu implementations
// catch up CPU backends
// fix precision issues
// add deletion functions for CPU backends
// macro tree for OpenCL
// split shade kernel
// simple textures
// texture atlas
// rethink 'shapes' in mesh description
// ray differentials
// sky and sun colors
// make render process incremental
