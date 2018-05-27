#include "RendererFactory.h"

#include "internal/RendererRef.h"
#if !defined(__ANDROID__)
#include "internal/RendererRef2.h"
#include "internal/RendererSSE.h"
#include "internal/RendererAVX.h"

#if !defined(DISABLE_OCL)
#include "internal/RendererOCL.h"
#else
#pragma message("Compiling without OpenCL support")
#endif
#else
#pragma message("Compiling without OpenCL support")
#endif

#include "internal/simd/detect.h"

std::shared_ptr<ray::RendererBase> ray::CreateRenderer(int w, int h, uint32_t flags, std::ostream &log_stream) {
    auto features = GetCpuFeatures();
#if !defined(__ANDROID__)
#if !defined(DISABLE_OCL)
    if (flags & RendererOCL) {
        log_stream << "ray: Creating OpenCL renderer " << w << "x" << h << std::endl;
        try {
            return std::make_shared<ocl::Renderer>(w, h);
        } catch (std::exception &e) {
            log_stream << "ray: Creating OpenCL renderer failed, " << e.what() << std::endl;
        }
    }
#endif
    if ((flags & RendererAVX) && features.avx_supported) {
        log_stream << "ray: Creating AVX renderer " << w << "x" << h << std::endl;
        return std::make_shared<avx::Renderer>(w, h);
    }
    if ((flags & RendererSSE) && features.sse2_supported) {
        log_stream << "ray: Creating SSE renderer " << w << "x" << h << std::endl;
        return std::make_shared<sse::Renderer>(w, h);
    }
    if (flags & RendererRef) {
        log_stream << "ray: Creating Ref renderer " << w << "x" << h << std::endl;
        return std::make_shared<ref::Renderer>(w, h);
    }
#endif
    log_stream << "ray: Creating Ref renderer " << w << "x" << h << std::endl;
    return std::make_shared<ref::Renderer>(w, h);
}