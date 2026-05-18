#include <stdint.h>

struct train_msg {
	uint32_t index;
	const char *msg;
};

extern const struct train_msg major_messages[];
extern const struct train_msg stream_messages_1d[];
extern const struct train_msg stream_messages_2d[];

uint32_t get_major_messages_num(void);
uint32_t get_stream_messages_1d_num(void);
uint32_t get_stream_messages_2d_num(void);