[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

color-map
---------------

**color-map** is a simple utility for interpolating between two given colors.

Useful for colorizing an output based on its value. For example, I use this utility for my [CPU module](https://github.com/proxict/dotfiles/blob/master/.config/i3/i3blocks/cpu-temp) of i3blocks.

Usage examples:
--------------
```bash
color-map "#00ff00" "#ff0000" ${CPU_TEMP}

color-map "#00ff00" "#ff0000" ${WIFI_SIGNAL_STRENGTH}

color-map "#00ff00" "#ff0000" ${MEM_USED_PERC}
```
