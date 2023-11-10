// INCLUDES
#include <stdio.h>
#include <stdint.h>
#include <cstring>
#include <math.h>
// DEFINES
#define IPV4_OCTATES 4
typedef struct SIP_INT_OCTATES {
	uint32_t fourth : 8;
	uint32_t third : 8;
	uint32_t second : 8;
	uint32_t first : 8;

} SIP_INT_OCTATES;
typedef union UIP_INT_ADDR {
	SIP_INT_OCTATES octates;
	uint32_t value;
}UIP_INT_ADDR;
// FUNCTIONS
void get_broadcast_address(int8_t *ip_addr, int8_t mask, int8_t *output_buffer);
uint32_t get_ip_integeral_equivalent(int8_t* ip_addr);
void get_abcd_ip_format(uint32_t ip_addr, int8_t *output_buffer);
void get_network_id(int8_t *ip_addr, int8_t mask, int8_t *output_buffer);
uint32_t get_number_from_string(int8_t* str);
uint32_t get_subnet_cardinality(int8_t mask);
int32_t check_ip_subnet_membership(int8_t *network_id, int8_t mask, int8_t *check_ip);