/*-------------------------------------------------------------------------
This source file is a part of OGRE
(Object-oriented Graphics Rendering Engine)

For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2011 Torus Knot Software Ltd
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE
-------------------------------------------------------------------------*/
#ifndef __OgrePrerequisites_H__
#define __OgrePrerequisites_H__

#include "CmPrerequisitesUtil.h"

#define CM_MAX_TEXTURE_LAYERS 16
#define CM_MAX_MULTIPLE_RENDER_TARGETS 8

namespace CamelotEngine {

// Pre-declare classes
// Allows use of pointers in header files without including individual .h
// so decreases dependencies between files
    class Camera;
    class Color;
    class Frustum;
    class GpuProgram;
    class GpuProgramManager;
	class GpuProgramUsage;
    class HardwareIndexBuffer;
    class HardwareOcclusionQuery;
    class HardwareVertexBuffer;
	class HardwarePixelBuffer;
	class HighLevelGpuProgram;
	class HighLevelGpuProgramManager;
	class HighLevelGpuProgramFactory;
    class IndexData;
    class Pass;
    class RenderSystem;
    class RenderSystemCapabilities;
    class RenderTarget;
    class RenderTexture;
	class MultiRenderTarget;
    class RenderWindow;
    class RenderOperation;
    class StringInterface;
    class TextureState;
    class Texture;
    class TextureManager;
    class Viewport;
    class VertexBufferBinding;
    class VertexData;
    class VertexDeclaration;
	// Asset import
	class SpecificImporter;
	class Importer;
	// Resources
	class Resource;
	class Resources;
}

/* Shared pointer typedefs*/
namespace CamelotEngine
{
	typedef std::shared_ptr<GpuProgram> GpuProgramPtr;
	typedef std::shared_ptr<HighLevelGpuProgram> HighLevelGpuProgramPtr;
	typedef std::shared_ptr<HardwarePixelBuffer> HardwarePixelBufferPtr;
	typedef std::shared_ptr<Texture> TexturePtr;
	typedef std::shared_ptr<Resource> ResourcePtr;
}

#endif // __OgrePrerequisites_H__

