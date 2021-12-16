#ifndef DADFS

#define DADFS

#define DADFS_MAGIC 0x10032013
#define DADFS_JOURNAL_MAGIC = 0x20032013

#define DADFS_DEFAULT_BLOCK_SIZE 4096
#define DADFS_FILENAME_MAXLEN 255
#define DADFS_START_INO 10
/**
 * Reserver inodes for super block, inodestore
 * and datablock
 */
#define DADFS_RESERVED_INODES 3

#ifdef DADFS_DEBUG
#define sfs_trace(fmt, ...) {                       \
	printk(KERN_ERR "[dadfs] %s +%d:" fmt,       \
	       __FILE__, __LINE__, ##__VA_ARGS__);      \
}
#define sfs_debug(level, fmt, ...) {                \
	printk(level "[dadfs]:" fmt, ##__VA_ARGS__); \
}
#else
#define sfs_trace(fmt, ...) no_printk(fmt, ##__VA_ARGS__)
#define sfs_debug(level, fmt, ...) no_printk(fmt, ##__VA_ARGS__)
#endif

/* Hard-coded inode number for the root directory */
const int DADFS_ROOTDIR_INODE_NUMBER = 1;

/* The disk block where super block is stored */
const int DADFS_SUPERBLOCK_BLOCK_NUMBER = 0;

/* The disk block where the inodes are stored */
const int DADFS_INODESTORE_BLOCK_NUMBER = 1;

/** Journal settings */
const int DADFS_JOURNAL_INODE_NUMBER = 2;
const int DADFS_JOURNAL_BLOCK_NUMBER = 2;
const int DADFS_JOURNAL_BLOCKS = 2;

/* The disk block where the name+inode_number pairs of the
 * contents of the root directory are stored */
const int DADFS_ROOTDIR_DATABLOCK_NUMBER = 4;

#define DADFS_LAST_RESERVED_BLOCK DADFS_ROOTDIR_DATABLOCK_NUMBER
#define DADFS_LAST_RESERVED_INODE DADFS_JOURNAL_INODE_NUMBER

/* The name+inode_number pair for each file in a directory.
 * This gets stored as the data for a directory */
struct dadfs_dir_record {
	char filename[DADFS_FILENAME_MAXLEN];
	uint64_t inode_no;
};

struct dadfs_inode {
	mode_t mode;
	uint64_t inode_no;
	uint64_t data_block_number;

	union {
		uint64_t file_size;
		uint64_t dir_children_count;
	};
};

const int DADFS_MAX_FILESYSTEM_OBJECTS_SUPPORTED = 64;
/* min (
		DADFS_DEFAULT_BLOCK_SIZE / sizeof(struct dadfs_inode),
		sizeof(uint64_t) //The free_blocks tracker in the sb
 	); */

/* FIXME: Move the struct to its own file and not expose the members
 * Always access using the dadfs_sb_* functions and
 * do not access the members directly */

struct journal_s;
struct dadfs_super_block {
	uint64_t version;
	uint64_t magic;
	uint64_t block_size;

	/* FIXME: This should be moved to the inode store and not part of the sb */
	uint64_t inodes_count;

	uint64_t free_blocks;

	/** FIXME: move this into separate struct */
	struct journal_s *journal;

	char padding[4048];
};

#endif // #ifndef DADFS
