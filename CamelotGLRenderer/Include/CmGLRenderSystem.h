/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org

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
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef __GLRenderSystem_H__
#define __GLRenderSystem_H__

#include "CmGLPrerequisites.h"
#include "CmRenderSystem.h"
#include "CmGLHardwareBufferManager.h"
#include "CmGLGpuProgramManager.h"
#include "CmGLSLProgramFactory.h"
#include "CmConfigOptionMap.h"
#include "CmCgProgramFactory.h"
#include "CmVector4.h"

namespace CamelotEngine {
    /**
      Implementation of GL as a rendering system.
     */
    class CM_RSGL_EXPORT GLRenderSystem : public RenderSystem
    {
    private:
        /// Rendering loop control
        bool mStopRendering;

        /// View matrix to set world against
        Matrix4 mViewMatrix;
        Matrix4 mWorldMatrix;
        Matrix4 mTextureMatrix;

        /// Last min & mip filtering options, so we can combine them
        FilterOptions mMinFilter;
        FilterOptions mMipFilter;

        /// What texture coord set each texture unit is using
        size_t mTextureCoordIndex[CM_MAX_TEXTURE_LAYERS];

        /// Holds texture type settings for every stage
        GLenum mTextureTypes[CM_MAX_TEXTURE_LAYERS];

		/// Number of fixed-function texture units
		unsigned short mFixedFunctionTextureUnits;

        void initConfigOptions(void);
        void initInputDevices(void);
        void processInputDevices(void);

        void makeGLMatrix(GLfloat gl_matrix[16], const Matrix4& m);
 
        GLint getBlendMode(SceneBlendFactor ogreBlend) const;
		GLint getTextureAddressingMode(SamplerState::TextureAddressingMode tam) const;
				void initialiseContext(RenderWindow* primary);

        void setLights();

        /// Store last depth write state
        bool mDepthWrite;
		/// Store last stencil mask state
		UINT32 mStencilMask;
		/// Store last colour write state
		bool mColourWrite[4];

        GLint convertCompareFunction(CompareFunction func) const;
        GLint convertStencilOp(StencilOperation op, bool invert = false) const;

		/// Internal method for anisotropy validation
		GLfloat _getCurrentAnisotropy(size_t unit);
		
        /// GL support class, used for creating windows etc.
        GLSupport* mGLSupport;

        bool mUseAutoTextureMatrix;
        GLfloat mAutoTextureMatrix[16];

        /// Check if the GL system has already been initialised
        bool mGLInitialised;

		GLSLProgramFactory* mGLSLProgramFactory;
		CgProgramFactory* mCgProgramFactory;

        unsigned short mCurrentLights;

        GLuint getCombinedMinMipFilter(void) const;

        GLGpuProgram* mCurrentVertexProgram;
        GLGpuProgram* mCurrentFragmentProgram;
		GLGpuProgram* mCurrentGeometryProgram;

		/* The main GL context - main thread only */
        GLContext *mMainContext;
        /* The current GL context  - main thread only */
        GLContext *mCurrentContext;
		typedef list<GLContext*>::type GLContextList;
		/// List of background thread contexts
		GLContextList mBackgroundContextList;

		UINT16 mActiveTextureUnit;

	protected:
		void setClipPlanesImpl(const PlaneList& clipPlanes);
		bool activateGLTextureUnit(size_t unit);
    public:
        // Default constructor / destructor
        GLRenderSystem();
        ~GLRenderSystem();

        // ----------------------------------
        // Overridden RenderSystem functions
        // ----------------------------------
        /** See
          RenderSystem
         */
        const String& getName(void) const;
        /** See
          RenderSystem
         */
        ConfigOptionMap& getConfigOptions(void);
        /** See
          RenderSystem
         */
        void setConfigOption(const String &name, const String &value);
        /** See
          RenderSystem
         */
        String validateConfigOptions(void);
        /** See
          RenderSystem
         */
        RenderWindow* startUp(bool runOnSeparateThread, bool autoCreateWindow, const String& windowTitle = "Camelot Render Window");
        /** See
          RenderSystem
         */
				virtual RenderSystemCapabilities* createRenderSystemCapabilities() const;
        /** See
          RenderSystem
         */
				void initialiseFromRenderSystemCapabilities(RenderSystemCapabilities* caps, RenderTarget* primary);
        /** See
          RenderSystem
         */
        void shutdown(void);
        
		/// @copydoc RenderSystem::createRenderWindow
		RenderWindow* createRenderWindow(const String &name, unsigned int width, unsigned int height, 
			bool fullScreen, const NameValuePairList *miscParams = 0);

		/// @copydoc RenderSystem::_createRenderWindows
		bool _createRenderWindows(const RenderWindowDescriptionList& renderWindowDescriptions, 
			RenderWindowList& createdWindows);

		
		/// @copydoc RenderSystem::createMultiRenderTarget
		virtual MultiRenderTarget * createMultiRenderTarget(const String & name); 
		
        /** See
          RenderSystem
         */
        void destroyRenderWindow(RenderWindow* pWin);
        /** See
          RenderSystem
         */
        String getErrorDescription(long errorNumber) const;

        /** See
          RenderSystem
         */
        VertexElementType getColorVertexElementType(void) const;

        // -----------------------------
        // Low-level overridden members
        // -----------------------------
        /** See
          RenderSystem
         */
		void setPointParameters(float size, bool attenuationEnabled, 
			float constant, float linear, float quadratic, float minSize, float maxSize);
		/** See
          RenderSystem
         */
        void setTexture(size_t unit, bool enabled, const TexturePtr &tex);
        /** See
          RenderSystem
         */
        void setTextureAddressingMode(size_t stage, const SamplerState::UVWAddressingMode& uvw);
        /** See
          RenderSystem
         */
        void setTextureBorderColor(size_t stage, const Color& colour);
		/** See
		  RenderSystem
		 */
		void setTextureMipmapBias(size_t unit, float bias);
        /** See
          RenderSystem
         */
        void setSceneBlending(SceneBlendFactor sourceFactor, SceneBlendFactor destFactor, SceneBlendOperation op );
        /** See
          RenderSystem
         */
		void setSeparateSceneBlending(SceneBlendFactor sourceFactor, SceneBlendFactor destFactor, SceneBlendFactor sourceFactorAlpha, SceneBlendFactor destFactorAlpha, SceneBlendOperation op, SceneBlendOperation alphaOp );
        /** See
          RenderSystem
         */
		void _setSceneBlendingOperation(SceneBlendOperation op);
		/** See
          RenderSystem
         */
		void _setSeparateSceneBlendingOperation(SceneBlendOperation op, SceneBlendOperation alphaOp);
		/** See
          RenderSystem
         */
        void setAlphaRejectSettings(CompareFunction func, unsigned char value, bool alphaToCoverage);
        /** See
          RenderSystem
         */
        void setViewport(Viewport *vp);
        /** See
          RenderSystem
         */
        void beginFrame(void);
        /** See
          RenderSystem
         */
        void endFrame(void);
        /** See
          RenderSystem
         */
        void setCullingMode(CullingMode mode);
        /** See
          RenderSystem
         */
        void setDepthBufferParams(bool depthTest = true, bool depthWrite = true, CompareFunction depthFunction = CMPF_LESS_EQUAL);
        /** See
          RenderSystem
         */
        void setDepthBufferCheckEnabled(bool enabled = true);
        /** See
          RenderSystem
         */
        void setDepthBufferWriteEnabled(bool enabled = true);
        /** See
          RenderSystem
         */
        void setDepthBufferFunction(CompareFunction func = CMPF_LESS_EQUAL);
        /** See
          RenderSystem
         */
        void setDepthBias(float constantBias, float slopeScaleBias);
        /** See
          RenderSystem
         */
        void setColorBufferWriteEnabled(bool red, bool green, bool blue, bool alpha);
        /** See
          RenderSystem
         */
        void _convertProjectionMatrix(const Matrix4& matrix,
            Matrix4& dest, bool forGpuProgram = false);
        /** See
          RenderSystem
         */
        void setClipPlane (UINT16 index, float A, float B, float C, float D);
        /** See
          RenderSystem
         */
        void enableClipPlane (UINT16 index, bool enable);
        /** See
          RenderSystem
         */
        void setPolygonMode(PolygonMode level);
        /** See
          RenderSystem
         */
        void setStencilCheckEnabled(bool enabled);
        /** See
          RenderSystem.
         */
        void setStencilBufferParams(CompareFunction func = CMPF_ALWAYS_PASS, 
            UINT32 refValue = 0, UINT32 mask = 0xFFFFFFFF, 
            StencilOperation stencilFailOp = SOP_KEEP, 
            StencilOperation depthFailOp = SOP_KEEP,
            StencilOperation passOp = SOP_KEEP, 
            bool twoSidedOperation = false);
        /** See
          RenderSystem
         */
        void setTextureFiltering(size_t unit, FilterType ftype, FilterOptions filter);
        /** See
          RenderSystem
         */
		void setTextureAnisotropy(size_t unit, unsigned int maxAnisotropy);
        /** See
          RenderSystem
         */
		void setVertexDeclaration(VertexDeclarationPtr decl);
        /** See
          RenderSystem
         */
		void setVertexBufferBinding(VertexBufferBinding* binding);
        /** See
          RenderSystem
         */
        void render(const RenderOperation& op);
        /** See
          RenderSystem
         */
        void bindGpuProgram(GpuProgram* prg);
        /** See
          RenderSystem
         */
        void unbindGpuProgram(GpuProgramType gptype);
        /** See
          RenderSystem
         */
		void bindGpuProgramParameters(GpuProgramType gptype, 
			GpuProgramParametersSharedPtr params, UINT16 variabilityMask);
        /** See
          RenderSystem
         */
        void setScissorTest(bool enabled, size_t left = 0, size_t top = 0, size_t right = 800, size_t bottom = 600) ;
        void clearFrameBuffer(unsigned int buffers, 
            const Color& colour = Color::Black, 
            float depth = 1.0f, unsigned short stencil = 0);
        float getHorizontalTexelOffset(void);
        float getVerticalTexelOffset(void);
        float getMinimumDepthInputValue(void);
        float getMaximumDepthInputValue(void);
		CM_MUTEX(mThreadInitMutex)
		void registerThread();
		void unregisterThread();

        // ----------------------------------
        // GLRenderSystem specific members
        // ----------------------------------
        /** One time initialization for the RenderState of a context. Things that
            only need to be set once, like the LightingModel can be defined here.
         */
        void _oneTimeContextInitialization();
        /** Switch GL context, dealing with involved internal cached states too
        */
        void _switchContext(GLContext *context);
        /**
         * Set current render target to target, enabling its GL context if needed
         */
        void setRenderTarget(RenderTarget *target);
        /** Unregister a render target->context mapping. If the context of target 
            is the current context, change the context to the main context so it
            can be destroyed safely. 
            
            @note This is automatically called by the destructor of 
            GLContext.
         */
        void _unregisterContext(GLContext *context);
		/** Returns the main context */
		GLContext* _getMainContext() {return mMainContext;} 

		/// @copydoc RenderSystem::getDisplayMonitorCount
		unsigned int getDisplayMonitorCount() const;
    };
}
#endif

