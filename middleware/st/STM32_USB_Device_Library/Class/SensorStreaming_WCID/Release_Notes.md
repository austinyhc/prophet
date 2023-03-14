---
pagetitle: Release Notes for SensorStreaming_WCID USB class 
lang: en
header-includes: <link rel="icon" type="image/x-icon" href="_htmresc/favicon.png" />
---

::: {.row}
::: {.col-sm-12 .col-lg-4}

<center>
# Release Notes for <mark>SensorStreaming_WCID USB class</mark>
Copyright &copy; 2022  STMicroelectronics\
    
[![ST logo](_htmresc/st_logo_2020.png)](https://www.st.com){.logo}
</center>


# Purpose

This middleware implements the USBD WCID streaming device class.

A Windows compatible ID (WCID) device is a USB device that provides extra information to a Windows system to
facilitate automated driver installation and, in most circumstances, allow immediate access.

This component is fully compliant with the modular and hierarchic structure of the STM32 USB-FS-Device
firmware library.

On top of the typical USB operations common to all USB classes (initialization, linking to the interface, etc.),
it provides functions to facilitate and enable fats data transfer up to 6Mbit/s.

:::

::: {.col-sm-12 .col-lg-8}
# Update History

::: {.collapse}
<input type="checkbox" id="collapse-section8" checked aria-hidden="true">
<label for="collapse-section8" aria-hidden="true">__v1.3.0 / 18-May-2022__</label>
<div>			

## Main Changes

### Maintenance release and product update

- Added header license neutral
- Added licence files

## Dependencies

This software component is compatible with STM32_USB_Device_Library up to v2.7.1

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section7" aria-hidden="true">
<label for="collapse-section7" aria-hidden="true">__v1.2.3 / 28-May-2021__</label>
<div>			

## Main Changes

### Patch release

- Bug fixed in USBD_WCID_STREAMING_Setup
- MISRA issue solved in USBD_VendDevReq 

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section6" aria-hidden="true">
<label for="collapse-section6" aria-hidden="true">__v1.2.2 / 13-Nov-2020__</label>
<div>			

## Main Changes

### Patch release

-  Memory issue fixed in USBD_WCID_STREAMING_DeInit function

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section5" aria-hidden="true">
<label for="collapse-section5" aria-hidden="true">__v1.2.1 / 19-Jun-2020__</label>
<div>			

## Main Changes

### Patch release

-  Solved MISRA warnings
-  Solved an issue in FillTxDataBuffer

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section4" aria-hidden="true">
<label for="collapse-section4" aria-hidden="true">__v1.2.0 / 03-Apr-2020__</label>
<div>			

## Main Changes

### Maitenance and patch release

-  Code refactoring for MISRA compliancy

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section3"  aria-hidden="true">
<label for="collapse-section3" aria-hidden="true">__v1.1.1 / 17-Jan-2020__</label>
<div>			

## Main Changes

### Patch release

-  Solved bug during init function and stop operations

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section2"  aria-hidden="true">
<label for="collapse-section2" aria-hidden="true">__v1.1.0 / 14-Nov-19__</label>
<div>			

## Main Changes

### Maintenance release

-  Added start and stop streaming functions

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section1"  aria-hidden="true">
<label for="collapse-section1" aria-hidden="true">__v1.0.0 / 24-Oct-2019__</label>
<div>			

## Main Changes

### First official release

- First official release

</div>
:::

:::
:::

<footer class="sticky">
::: {.columns}
::: {.column width="95%"}
For complete documentation,
visit: [www.st.com](http://www.st.com/STM32)
:::
::: {.column width="5%"}
<abbr title="Based on template cx566953 version 2.0">Info</abbr>
:::
:::
</footer>