//__________________________ Banshee Project - A modern game development toolkit _________________________________//
//_____________________________________ www.banshee-project.com __________________________________________________//
//________________________ Copyright (c) 2014 Marko Pintera. All rights reserved. ________________________________//
#pragma once

#include "BsD3D11Prerequisites.h"
#include "BsRenderStateManager.h"

namespace BansheeEngine
{
	/**
	 * @brief	Handles creation of DirectX 11 pipeline states.
	 */
	class BS_D3D11_EXPORT D3D11RenderStateManager : public RenderStateManager
	{
	protected:
		/**
		 * @copydoc	RenderStateManager::createSamplerStateImpl
		 */
		virtual SamplerStatePtr createSamplerStateImpl() const;

		/**
		 * @copydoc	RenderStateManager::createBlendStateImpl
		 */
		virtual BlendStatePtr createBlendStateImpl() const;

		/**
		 * @copydoc	RenderStateManager::createRasterizerStateImpl
		 */
		virtual RasterizerStatePtr createRasterizerStateImpl() const;

		/**
		 * @copydoc	RenderStateManager::createDepthStencilStateImpl
		 */
		virtual DepthStencilStatePtr createDepthStencilStateImpl() const;
	};
}