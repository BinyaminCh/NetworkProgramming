
// Calculate broadcast address
// Input : ip address string, mask
// Output - broadcast address string
void get_broadcast_address(char *ip_addr, char mask, char *output_buffer);
// Calculate ip integeral value
// Receive ip address string, return ip integeral value
unsigned int get_ip_integeral_equivalent(char *ip_address);
// Calculate ip string from ip integer value
void get_abcd_ip_format(unsigned int ip_address, char *output_buffer);
// Calculate network id from ip address string and mask
void get_network_id(char *ip_addr, char mask, char *output_buffer);
// Calculate subnet cardinality from mask value
unsigned int get_subnet_cardinality(char mask);
// Check if ip address is member in subnet with specific network id and mask value
// Return 0 if true, else -1
int check_ip_subnet_membership(char *network_id, char mask, char *check_ip);