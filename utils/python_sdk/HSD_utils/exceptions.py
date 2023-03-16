# *****************************************************************************
#  * @file    exceptions.py
#  * @author  SRA
# ******************************************************************************
# * @attention
# *
# * Copyright (c) 2022 STMicroelectronics.
# * All rights reserved.
# *
# * This software is licensed under terms that can be found in the LICENSE file
# * in the root directory of this software component.
# * If no LICENSE file comes with this software, it is provided AS-IS.
# *
# *
# ******************************************************************************
#

class HSDError(Exception):
    pass

class MissingDeviceModelError(HSDError):
    pass

class MissingSensorModelError(HSDError):
    pass

class MissingAcquisitionInfoError(HSDError):
    pass

class SensorParamsError(HSDError):
     def __init__(self, sensor_name):
         super().__init__("{}".format(sensor_name))

class SensorIDError(SensorParamsError):
    pass

class SubSensorIDError(SensorParamsError):
    pass

class SubSensorTypeError(SensorParamsError):
    pass

class NSensorAxesError(SensorParamsError):
    pass

class MissingFileForSensorError(HSDError):
    def __init__(self, file_path, sensor_name):
        super().__init__("{} --x {}".format(file_path, sensor_name))

class DataExtractionError(HSDError):
    def __init__(self, sensor_name, sensor_type):
        super().__init__("{}_{}".format(sensor_name,sensor_type))

class NoDataAtIndexError(HSDError):
    def __init__(self, index, file_path, size):
        super().__init__("index: {}, file: {}, size: {}".format(index,file_path,size))

class NanoEdgeConversionError(HSDError):
    def __init__(self, sensor_name):
         super().__init__("{}".format(sensor_name))

class NoDeviceConnectedError(HSDError):
    pass

class InvalidCommandSetError(HSDError):
    def __init__(self, dev_com_set):
         super().__init__("{}".format(dev_com_set))

class UnsupportedPlatformError(HSDError):
    def __init__(self, platform):
         super().__init__("{}".format(platform))

class HSDLibError(HSDError):
    def __init__(self, command_name):
         super().__init__("{}".format(command_name))

class MemoryFreeError(HSDLibError):
    def __init__(self):
         super().__init__("{}".format("__hs_datalog_free"))

class CommunicationEngineOpenError(HSDLibError):
    def __init__(self):
         super().__init__("{}".format("hs_datalog_open"))

class CommunicationEngineCloseError(HSDLibError):
    def __init__(self):
         super().__init__("{}".format("hs_datalog_close"))

class EmptyCommandResponse(HSDLibError):
    pass

class SETCommandError(HSDLibError):
    pass