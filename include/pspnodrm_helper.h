#ifndef NODRM
#define NODRM

#include <pspkernel.h>
#include <pspamctrl.h>

typedef struct {
	u8  vkey[16];

	int open_flag;
	int key_index;
	int drm_type;
	int mac_type;
	int cipher_type;

	int data_size;
	int align_size;
	int block_size;
	int block_nr;
	int data_offset;
	int table_offset;

	u8 *buf;
} PGD_DESC;

int sceUtilsBufferCopyWithRange(u8 *outbuf, int outlen, u8 *inbuf, int inlen, int cmd);

int kirk7(u8 *buf, int size, int type);

/**
 * Gets the version key from a file path.
 *
 * @param[out] version_key A buffer to receive the version key.
 * @param[in] path A file path to use.
 *
 * @returns `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspnodrm_helper` stub to be available.
 *
 * @note Available on ARK (>= 5.1.0) and Epinephrine (>= 8.1.0).
 */
int nodrmGetVersionKey(u8 *version_key, const char *path);


/**
 * Gets the EDAT key.
 *
 * @attention Requires linking to `pspnodrm_helper` stub to be available.
 *
 * @note Available on ARK (>= 5.1.0) and Epinephrine (>= 8.1.0).
 */
int nodrmGetEdatKey(u8 *vkey, u8 *pgd_buf);

/**
 * Gets Mac Key.
 *
 * @attention Requires linking to `pspnodrm_helper` stub to be available.
 *
 * @note Available on ARK (>= 5.1.0) and Epinephrine (>= 8.1.0).
 */
int nodrmBBMacGetKey(SceMacKey *mkey, u8 *bbmac, u8 *vkey);

#endif /* NODRM */
