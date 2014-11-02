#ifndef MISC_H
#define MISC_H

#define DEPTH_LVL_0 0.0f
#define DEPTH_LVL_1 1.0f
#define DEPTH_LVL_2 2.0f
#define DEPTH_LVL_3 3.0f
#define DEPTH_LVL_4 4.0f
#define DEPTH_LVL_5 5.0f
#define DEPTH_LVL_6 6.0f
#define DEPTH_LVL_7 7.0f
#define DEPTH_LVL_8 8.0f
#define DEPTH_LVL_9 9.0f

#define SEC_TO_TICK 100.0f

template <class T> void SafeRelease(T **ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = nullptr;
	}
}

namespace DX
{
	inline void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			throw hr;
		}
	}

#if defined(_DEBUG)

#include <Windows.h>
#include <d3d11_2.h>

	// Check for SDK Layer support.
	inline bool SdkLayersAvailable()
	{
		HRESULT hr = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_NULL,       // There is no need to create a real hardware device.
			0,
			D3D11_CREATE_DEVICE_DEBUG,  // Check for the SDK layers.
			nullptr,                    // Any feature level will do.
			0,
			D3D11_SDK_VERSION,          // Always set this to D3D11_SDK_VERSION for Windows Store apps.
			nullptr,                    // No need to keep the D3D device reference.
			nullptr,                    // No need to know the feature level.
			nullptr                     // No need to keep the D3D device context reference.
			);

		return SUCCEEDED(hr);
	}
#endif
}


#endif // MISC_H