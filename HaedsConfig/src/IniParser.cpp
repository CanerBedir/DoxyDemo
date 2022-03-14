// =============================================================================
// File: IniParser.cpp
// (C) Copyright KONGSBERG 2022.
// All rights reserved.
// -----------------------------------------------------------------------------
// Classification: UGRADERT
// -----------------------------------------------------------------------------
// Written by Mustafa Tutuncu (tutuncu@altay.com.tr)
// -----------------------------------------------------------------------------

#include "IniParser.h"

#include <algorithm>

namespace Haeds {
   namespace Config {
      bool
      IniParser::_testConfigFileExists()
      {
         //// Check config file exists or not
         //// C++11 and 14
         //std::ifstream file(CONFIGFILE);
         //if (!file.is_open()) {
         //   std::cout << "Configuration file not found!" << std::endl;
         //   return false;
         //}

         // C++ 17
         namespace fs = std::filesystem;
         fs::path f{ _configFile };
         if (!fs::exists(f)) {
            //std::cout << "Configuration file not found!" << std::endl;
            _resultMsg = "ERR:Configuration file not found";
            return false;
         }

         return true;
      }

      bool
      IniParser::_testAndLoadConfigFileContent() 
      {
         INIReader iniReader(_configFile);

         if (iniReader.ParseError() < 0) {
            _resultMsg = "Haeds Proto Config File Test: Parse FAILED!";
            return false;
         }

         _sections = iniReader.Sections();

         _videoFrameWidth = iniReader.GetInteger("Video", "FrameWidth", -1);
         if (_videoFrameWidth == -1) {
            _resultMsg = "Haeds Proto Config File Test: Video:FrameWidth FAILED!";
            return false;
         };

         _videoFrameHeight = iniReader.GetInteger("Video", "FrameHeight", -1);
         if (_videoFrameHeight == -1) {
            _resultMsg = "Haeds Proto Config File Test: Video:FrameHeight FAILED!";
            return false;
         };

         _videoCodec = iniReader.Get("Video", "Codec", "NotFound");
         if (_videoCodec == "NotFound") {
            _resultMsg = "Haeds Proto Config File Test: Video:Codec FAILED!";
            return false;
         };
         _videoCodec.erase(std::remove(_videoCodec.begin(), _videoCodec.end(), '\"'), _videoCodec.end());

         _videoFrameRate = iniReader.GetFloat("Video", "FrameRate", -1.0f);
         if (_videoFrameRate == -1.0f) {
            _resultMsg = "Haeds Proto Config File Test: Video:FrameRate FAILED!";
            return false;
         };

         _videoStreamCount = iniReader.GetInteger("Video", "StreamCount", -1);
         if (_videoStreamCount == -1) {
            _resultMsg = "Video:StreamCount FAILED!";
            return false;
         };

         _videoMaxH265EncDelay = iniReader.GetInteger("Video", "MaxH265EncDelay", -1);
         if (_videoMaxH265EncDelay == -1) {
            _resultMsg = "Video:MaxH265EncDelay FAILED!";
            return false;
         };

         _videoIFrameInterval = iniReader.GetInteger("Video", "IFrameInterval", -1);
         if (_videoIFrameInterval == -1) {
            _resultMsg = "Video:IFrameInterval FAILED!";
            return false;
         };

         _decoderSharedMemoryBufferSize = iniReader.GetInteger("DecoderSharedMemory", "BufferSize", -1);
         if (_decoderSharedMemoryBufferSize == -1) {
            _resultMsg = "DecoderSharedMemory:BufferSize FAILED!";
            return false;
         };

         _decoderSharedMemoryTextSize = iniReader.GetInteger("DecoderSharedMemory", "TextSize", -1);
         if (_decoderSharedMemoryTextSize == -1) {
            _resultMsg = "DecoderSharedMemory:TextSize FAILED!";
            return false;
         };

         _networkBandWidth = iniReader.GetInteger("Network", "BandWidth", -1);
         if (_networkBandWidth == -1) {
            _resultMsg = "Network:BandWidth FAILED!";
            return false;
         };

         _debugStatus = iniReader.GetInteger("Debug", "Status", -1);
         if (_debugStatus == -1) {
            _resultMsg = "Debug:Status FAILED!";
            return false;
         };
         _debugOutput = iniReader.GetInteger("Debug", "Output", -1);
         if (_debugOutput == -1) {
            _resultMsg = "Debug:Output FAILED!";
            return false;
         };
         _debugLogLevel = iniReader.Get("Debug", "LogLevel", "NotFound");
         if (_debugFileName == "NotFound") {
            _resultMsg = "Debug:FileName FAILED!";
            return false;
         };
         _debugLogLevel.erase(std::remove(_debugLogLevel.begin(), _debugLogLevel.end(), '\"'), _debugLogLevel.end());

         _debugFileName = iniReader.Get("Debug", "FileName", "NotFound");
         if (_debugFileName == "NotFound") {
            _resultMsg = "Debug:FileName FAILED!";
            return false;
         };
         _debugFileName.erase(std::remove(_debugFileName.begin(), _debugFileName.end(), '\"'), _debugFileName.end());

         return true;
      }

      IniParser::IniParser() {
         IniParser( CONFIGFILE);
         _resultCode = 0;
         _resultMsg = "OK ";
      }

      IniParser::IniParser(const std::string pConfigFileName)
      {
         _configFile = pConfigFileName;
         _videoFrameWidth = 0;
         _videoFrameHeight = 0;
         _videoCodec = "";
         _videoFrameRate = 0.0F;
         _videoStreamCount = 0;
         _videoMaxH265EncDelay = 0;
         _videoIFrameInterval = 0;
         _decoderSharedMemoryBufferSize = 0;
         _decoderSharedMemoryTextSize = 0;
         _networkBandWidth = 0;
         _debugStatus = 0;
         _debugOutput = 0;
         _debugFileName = "";

         if (!_testConfigFileExists()) {
            _resultCode = 1; // Configuration file not found. Actual message is in the resultMsg.
            return;
         };

         if (!_testAndLoadConfigFileContent()) {
            _resultCode = 2; // Configuration file content error. Actual message is in the resultMsg.
            return;
         };

         _resultCode = 0;
         _resultMsg = "OK ";
      }

      void
      IniParser::dumpProperties() {
         std::cout << "Video:FrameWidth (pix): " << this->videoFrameWidth << std::endl;
         std::cout << "Video:FrameHeight (pix): " << this->videoFrameHeight << std::endl;
         std::cout << "Video:Codec: " << this->videoCodec << std::endl;
         std::cout << "Video:FrameRate (fps): " << this->videoFrameRate << std::endl;
         std::cout << "Video:StreamCount: " << this->videoStreamCount << std::endl;
         std::cout << "Video:MaxH265EncDelay: " << this->videoMaxH265EncDelay << std::endl;
         std::cout << "Video:IFrameInterval: " << this->videoIFrameInterval << std::endl;
         std::cout << "DecoderSharedMemory:BufferSize: " << this->decoderSharedMemoryBufferSize << std::endl;
         std::cout << "DecoderSharedMemory:TextSize: " << this->decoderSharedMemoryTextSize << std::endl;
         std::cout << "Network:BandWidth (Mbps): " << this->networkBandWidth << std::endl;
         std::cout << "Debug:Status: " << this->debugStatus << std::endl;
         std::cout << "Debug:Output: " << this->debugOutput << std::endl;
         std::cout << "Debug:LogLevel: " << this->debugLogLevel << std::endl;
         std::cout << "Debug:FileName: " << this->debugFileName << std::endl;
      }

      std::set<std::string>
      IniParser::getSections() {
         return _sections; 
      }

      int32_t
      IniParser::getResultCode() {
         return _resultCode;
      }

      std::string
      IniParser::getResultMsg() {
         return _resultMsg;
      }

      int32_t
      IniParser::getVideoFrameWidth() {
         return _videoFrameWidth;
      }

      int32_t
      IniParser::getVideoFrameHeight() {
         return _videoFrameHeight;
      }

      std::string
      IniParser::getVideoCodec() {
         return _videoCodec;
      }

      float_t 
      IniParser::getVideoFrameRate() {
         return _videoFrameRate;
      }

      int32_t
      IniParser::getVideoStreamCount() {
         return _videoStreamCount;
      }

      int32_t
      IniParser::getVideoMaxH265EncDelay() {
         return _videoMaxH265EncDelay;
      }

      int32_t
         IniParser::getVideoIFrameInterval() {
         return _videoIFrameInterval;
      }

      int32_t 
          IniParser::getDecoderSharedMemoryBufferSize() {
          return _decoderSharedMemoryBufferSize;
      }

      int32_t 
          IniParser::getDecoderSharedMemoryTextSize() {
          return _decoderSharedMemoryTextSize;
      }

      int32_t 
          IniParser::getNetworkBandWidth() {
          return _networkBandWidth;
      }

      int32_t 
          IniParser::getDebugStatus() {
          return _debugStatus;
      }
      int32_t 
          IniParser::getDebugOutput() {
          return _debugOutput;
      }
      std::string
          IniParser::getDebugLogLevel() {
          return _debugLogLevel;
      }
      std::string
      IniParser::getDebugFileName() {
          return _debugFileName;
      }
   }

   //namespace Utils
   //{
   //   bool isSetContainsSet(std::set<std::string>& set1, std::set<std::string>& set2) {
   //      bool result = true;
   //      auto itBegin = set2.begin();
   //      auto itEnd = set2.end();
   //      for (auto it = itBegin; it != itEnd; it++)
   //      {
   //         //std::cout << *it << " ";
   //         if (!set1.count(*it))
   //         {
   //            result = false;
   //            exit;
   //         }
   //      }
   //      return result;
   //   }
   //   size_t getFileSizeAsByte(FILE* file)
   //   {
   //      int32_t lCurPos;
   //      int32_t lEndPos;
   //      lCurPos = ftell(file);          // Get file's current position as bytes into lCurPos.
   //      fseek(file, 0, SEEK_END);       // Go to 0 bytes from end of file. We are end of file now.
   //      lEndPos = ftell(file);          // Get file's current position into lEndPos which is file length as bytes.
   //      fseek(file, lCurPos, SEEK_SET); // Go to lCurPos bytes from beginning of file.
   //      return lEndPos;
   //   };
   //}
}
