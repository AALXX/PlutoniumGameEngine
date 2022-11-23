#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <vulkan/vulkan.hpp>

namespace PGE_VULKAN {

	std::vector<char> readFile(std::string filename, bool debug) {

		std::ifstream file(filename, std::ios::ate | std::ios::binary);

		if (debug && !file.is_open()) {
			PGE_CORE_ERROR("Failed to load");
		}

		size_t filesize{ static_cast<size_t>(file.tellg()) };

		std::vector<char> buffer(filesize);
		file.seekg(0);
		file.read(buffer.data(), filesize);

		file.close();
		return buffer;
	}

	vk::ShaderModule createModule(std::string filename, vk::Device device, bool debug) {

		std::vector<char> sourceCode = readFile(filename, debug);
		vk::ShaderModuleCreateInfo moduleInfo = {};
		moduleInfo.flags = vk::ShaderModuleCreateFlags();
		moduleInfo.codeSize = sourceCode.size();
		moduleInfo.pCode = reinterpret_cast<const uint32_t*>(sourceCode.data());

		try {
			return device.createShaderModule(moduleInfo);
		}
		catch (vk::SystemError err) {
			if (debug) {
				PGE_CORE_ERROR("failed to create shader module for  \"{0}\" ", filename);

			}
		}
	}

}