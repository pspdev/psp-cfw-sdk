/*
	Unified UMDemu ISO driver API
	Copyright (C) 2016-2018, TheFloW
	Copyright (C) 2024-2025, isage
	Copyright (C) 2025, GrayJack

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * Header for the unified API of the UMDemu ISO drivers: Inferno, March33 and Galaxy (NP9660).
 *
 * To use the functions, it is required to link to one of the driver stubs.
 * - `libpspisoctrl_driver`: unified for all UMDemu ISO drivers of Adrenaline
 * - `libpspinferno_driver`
 * - `libpspmarch33_driver`
 * - `libpspgalaxy_driver`
 */

#ifndef ISO_CTRL_H
#define ISO_CTRL_H

#include <psptypes.h>

#define MAX_ISO_PATH_SIZE 256

enum UmdDelayStrategy {
	UMD_DELAY_STRAT_PER_FD = 0,
	UMD_DELAY_STRAT_GLOBAL = 1,
};

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/**
 * Issue a direct ISO/CSO read request to the UMDemu ISO driver.
 *
 * @param offset The offset/sector within the Virtual UMD to start reading from. Absolute Offset.
 * @param[out] buf The buffer to write data to.
 * @param size The amount of bytes to read.
 *
 * @return The amount of bytes read, `< 0` on error.
 *
 * @attention Requires linking to `pspisoctrl_driver` stub to be available.
 */
int isoReadUmdFile(u32 offset, void *buf, u32 size);

/**
 * Sets UMD speed simulation.
 *
 * @param seek The seek delay factor. `0` to disable, `> 0` to enable, the higher the value the slower the seek time.
 * @param speed The read speed delay factor. `0` to disable, `> 0` to enable, the higher the value the slower the read time.
 * @param strategy The delay strategy to use. One of `UmdDelayStrategy`.
 *
 * @attention Requires linking to `pspisoctrl_driver` stub to be available.
 */
void isoSetUmdDelay(int seek, int speed, int strategy);

/**
 * Gets the Title ID of the ISO/CSO file of the UMDemu ISO driver.
 *
 * @param[out] title_id The string buffer to write the data into.
 *
 * @return `0` if getting the Title ID fails, `1` if succeeded.
 *
 * @attention Requires linking to `pspisoctrl_driver` stub to be available.
 */
int isoGetTitleId(char title_id[10]);

/**
 * Sets the UMD ISO/CSO file of the UMDemu ISO driver.
 *
 * @param[in] path The file path to set.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspisoctrl_driver` stub to be available.
 */
int isoSetUmdFile(const char *path);

/**
 * Gets the current UMD ISO/CSO file set for the UMDemu ISO driver.
 *
 * @param[out] path_buf The buffer to receive the current UMD file.
 * @param path_size The size of the buffer to receive the current UMD file.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspisoctrl_driver` stub to be available.
 */
int isoGetUmdFile(char *path_buf, SceSize path_size);

/**
 * Reopens the set UMD ISO/CSO file.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspisoctrl_driver` stub to be available.
 */
int isoReopenUmdFile(void);

/**
 * Swaps the current UMD ISO/CSO file with a new.
 *
 * @param[in] new_file_path The new ISO file to set.
 * @param[out] previous A buffer to receive the previously set UMD ISO/CSO file.
 * 	Pass `NULL` if this information is not desired.
 * @param previous_size The size of the `previous` buffer. This needs to be at
 * 	least `MAX_ISO_PATH_SIZE` otherwise it won't copy the information.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspisoctrl_driver` stub to be available.
 */
int isoSwapUmdFile(const char *new_file_path, char *previous, SceSize previous_size);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // ISO_CTRL_H