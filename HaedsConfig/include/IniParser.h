// =============================================================================
// File: IniParser.h
// (C) Copyright KONGSBERG 2022.
// All rights reserved.
// -----------------------------------------------------------------------------
// Classification: UGRADERT
// -----------------------------------------------------------------------------
// Written by Mustafa Tutuncu (tutuncu@altay.com.tr)
// -----------------------------------------------------------------------------

#ifndef INIPARSER_H
#define INIPARSER_H

#include <INIreader.h>

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <cstdint>
#include <math.h>
#include <set>

///
/// @brief Haeds: Project top level namespace
//
namespace Haeds
{
   ///
   /// @brief Haeds::Config: Configuration module namespace
   //
   namespace Config
   {
      constexpr auto CONFIGFILE{ "data/config.ini" };
      
      ///
      /// @brief IniParser: INI file parser class
      //
      class IniParser {
         private:
            std::string _configFile;
            int32_t _resultCode;
            std::string _resultMsg;
            int32_t _videoFrameWidth;
            int32_t _videoFrameHeight;
            std::string _videoCodec;
            float_t _videoFrameRate;
            int32_t _videoStreamCount;
            int32_t _videoMaxH265EncDelay;
            int32_t _videoIFrameInterval;
            int32_t _decoderSharedMemoryBufferSize;
            int32_t _decoderSharedMemoryTextSize;
            int32_t _networkBandWidth;
            int32_t _debugStatus;
            int32_t _debugOutput;
            std::string _debugLogLevel;
            std::string _debugFileName;

            std::set<std::string> _sections;
            bool _testConfigFileExists();
            bool _testAndLoadConfigFileContent();

         public:
            const int32_t& resultCode = _resultCode;
            const std::string& resultMsg = _resultMsg;
            const int32_t& videoFrameWidth = _videoFrameWidth;
            const int32_t& videoFrameHeight = _videoFrameHeight;
            const std::string& videoCodec = _videoCodec;
            const float_t& videoFrameRate = _videoFrameRate;
            const int32_t& videoStreamCount = _videoStreamCount;
            const int32_t& videoMaxH265EncDelay = _videoMaxH265EncDelay;
            const int32_t& videoIFrameInterval = _videoIFrameInterval;
            const int32_t& decoderSharedMemoryBufferSize = _decoderSharedMemoryBufferSize;
            const int32_t& decoderSharedMemoryTextSize = _decoderSharedMemoryTextSize;
            const int32_t& networkBandWidth = _networkBandWidth;
            const int32_t& debugStatus = _debugStatus;
            const int32_t& debugOutput = _debugOutput;
            const std::string& debugLogLevel = _debugLogLevel;
            const std::string& debugFileName = _debugFileName;

            IniParser();
            IniParser(const std::string pConfigFileName);
            
            ///
            /// @brief Dumps INI file's all sections and related keys/values
            /// 
            /// @param void
            /// 
            /// @return void
            // 
            void dumpProperties();

            ///
            /// @brief Gets all sections of INI file
            /// 
            /// @param void
            /// 
            /// @return All sections of INI file as set of strings
            /// 
            /// @retval std::set<std::string>
            //
            std::set<std::string> getSections();

            ///
            /// @brief Gets result code of IniParser class initializing
            /// 
            /// @param void
            /// 
            /// @return result code of initializing
            /// 
            /// @retval 0 The initializing is successfully executed
            /// @retval 1 Configuration file not found. Actual message is in the resultMsg.
            /// @retval 2 Configuration file content error. Actual message is in the resultMsg.
            //
            int32_t getResultCode();

            std::string getResultMsg();
            int32_t getVideoFrameWidth();
            int32_t getVideoFrameHeight();
            std::string getVideoCodec();
            float_t getVideoFrameRate();
            int32_t getVideoStreamCount();
            int32_t getVideoMaxH265EncDelay();
            int32_t getVideoIFrameInterval();
            int32_t getDecoderSharedMemoryBufferSize();
            int32_t getDecoderSharedMemoryTextSize();
            int32_t getNetworkBandWidth();
            int32_t getDebugStatus();
            int32_t getDebugOutput();
            std::string getDebugLogLevel();
            std::string getDebugFileName();
      };

      using spIniParser = std::unique_ptr<Haeds::Config::IniParser>;
   }   
}
#endif
