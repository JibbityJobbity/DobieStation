#pragma once

#ifdef WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#ifdef __APPLE__
#define VK_USE_PLATFORM_MACOS_MVK
#endif

#ifdef HAVE_X11
#define VK_USE_PLATFORM_XLIB_KHR
#endif

// We'll use our own function definitions
#define VK_NO_PROTOTYPES

#include <vulkan/vulkan.h>
#include <vector>
#include <array>

namespace Vulkan
{
// types
using u32 = uint32_t;
using u16 = uint16_t;
using u8  = uint8_t;

using i32 = int32_t;
using i16 = int16_t;
using i8  = int8_t;

using layer_properties_list_t = std::vector<VkLayerProperties>;
using extension_list_t        = std::vector<VkExtensionProperties>;
using physical_device_list_t  = std::vector<VkPhysicalDevice>;
using queue_properties_list_t = std::vector<VkQueueFamilyProperties>;
using format_list_t           = std::vector<VkSurfaceFormatKHR>;
using name_list_t             = std::vector<const char*>;

bool load();
void unload();

void log(const char* fmt, ...);
void hook_or_die(const char* file, int line, VkResult res);

// extern PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
// extern PFN_vkCreateInstance vkCreateInstance;
// ...
#define VK_GLOBAL_FUNC(func) extern PFN_##func func;
#include "vulkan.inl"

#define VK_MODULE_FUNC(func) extern PFN_##func func;
#include "vulkan.inl"

#define VK_INSTANCE_FUNC(func) extern PFN_##func func;
#include "vulkan.inl"

#define VK_DEVICE_FUNC(func) extern PFN_##func func;
#include "vulkan.inl"

// For windows I define this in the
// build configuration for debug/devel
#ifdef VIDEO_DEBUG_LOG
#define LOG_VIDEO(fmt, ...) Vulkan::log(fmt, ##__VA_ARGS__)
#else
#define LOG_VIDEO(fmt, ...)
#endif

// Quick way to die on failed vk result
#define CHECK_RESULT(expr)                              \
{                                                       \
    VkResult _res = (expr);                             \
    if(_res != VK_SUCCESS)                              \
        Vulkan::hook_or_die(__FILE__, __LINE__, _res);  \
}                                                       \

#define VK_FAILED(expr) (expr) != VK_SUCCESS
}