#include "IP_MATHS.h"
/*
* Get broadcast address
* input - ip address in string, mask value
* output - string of broadcast address
*/
void get_broadcast_address(int8_t *ip_addr, int8_t mask, int8_t *output_buffer) {
    UIP_INT_ADDR uip_addr;
    uint32_t binary_num = 0xffffffff;
    binary_num <<= (32 - mask);
    // get ip in integral
    uip_addr.value = get_ip_integeral_equivalent(ip_addr);
    get_network_id(ip_addr, mask, output_buffer);
    // get network id in integral value
    uip_addr.value = get_ip_integeral_equivalent(output_buffer);
    // calculate broadcast address
    uip_addr.value = uip_addr.value | (~binary_num);
    // output broadcast address
    get_abcd_ip_format(uip_addr.value, output_buffer);
}
/*
* Function to get ip integeral value from ip address string
*/uint32_t get_ip_integeral_equivalent(int8_t *ip_addr) {
    uint32_t octates[IPV4_OCTATES];
    UIP_INT_ADDR uip_addr;
    memset(&uip_addr, 0, sizeof(uip_addr));
    memset(&octates, 0, sizeof(octates));
    uint8_t current_oct = 0;
    int8_t octStr[4];
    uint8_t octStrIndex = 0;

    while ((ip_addr != NULL) && (*ip_addr != '\0')) {
        if (*ip_addr == '.') {
            octStr[octStrIndex] = '\0';
            octates[current_oct++] = get_number_from_string(octStr);
            memset(&octStr, 0, sizeof(octStr));
            octStrIndex = 0;
        }
        else {
            octStr[octStrIndex] = *ip_addr;
            octStrIndex++;
        }
        ip_addr++;

        if (*ip_addr == '\0') {
            octates[current_oct++] = get_number_from_string(octStr);
        }
    }

    uip_addr.octates.first = octates[0];
    uip_addr.octates.second = octates[1];
    uip_addr.octates.third = octates[2];
    uip_addr.octates.fourth = octates[3];

    return uip_addr.value;
}
/*
* Function to get a string of ip address from ip integral value
*/
void get_abcd_ip_format(uint32_t ip_addr, int8_t *output_buffer) {
    UIP_INT_ADDR uip_addr;
    uip_addr.value = ip_addr;
    uint32_t multiplier = 1;
    uint32_t buffer_index = 0;

    sprintf((char*)output_buffer, "%d.%d.%d.%d", uip_addr.octates.first, uip_addr.octates.second, uip_addr.octates.third, uip_addr.octates.fourth);
    int x = 0;
}
/*
* Get network id from ip address string and mask value
* Output - string
*/
void get_network_id(int8_t *ip_addr, int8_t mask, int8_t *output_buffer) {
    uint32_t binary_num = 0xffffffff;
    binary_num <<= (32 - mask);
    UIP_INT_ADDR uip_addr;
    memset(&uip_addr, 0, sizeof(uip_addr));

    uip_addr.value = get_ip_integeral_equivalent(ip_addr);
    uip_addr.value = uip_addr.value & binary_num;
    get_abcd_ip_format(uip_addr.value, output_buffer);

}
/*
* Returns how many usable ip addresses exist for given mask
*/
uint32_t get_subnet_cardinality(int8_t mask) {
    uint32_t subnet_cardinality = pow(2, 32 - mask) - 2;

    
    return subnet_cardinality;
}
/*
* Function to convert a string to an integer
*/
uint32_t get_number_from_string(int8_t *str) {
    uint32_t num = 0;
    int8_t sign_multiplier = 1;
    uint32_t multiplier = 1;
    uint16_t len = 0;
    int8_t *temp = str;
    // IF NO INPUT TO FUNCTION OR INPUT INVALID
    if ((str == NULL) || (*str == '\0')) {
        return num;
    }
    // IF NEGATIVE NUM, CHANGE SIGN MULTIPLIER
    if (*temp == '-') {
        sign_multiplier *= -1;
        // GO TO NEXT int8_tACTER
        temp++;
        str++;
    }
    // GET LEN
    while (*temp != '\0') {
        len++;
        temp++;
    }
    // SET MULTIPLIER
    for (int i = 0; i < len - 1 ; ++i) {
        multiplier *= 10;
    }
    while (*str != '\0') {
        if (*str >= '0' && *str <= '9') {
            num += ((*str - '0') * multiplier);
        }
        multiplier /= 10;
        str++;
    }

    return num * sign_multiplier;
}

int32_t check_ip_subnet_membership(int8_t *network_id, int8_t mask, int8_t *check_ip) {
    UIP_INT_ADDR uip_addr_networkid;
    UIP_INT_ADDR uip_addr_iptocheck;
    UIP_INT_ADDR uip_addr_ipcheckNetworkId;
    int8_t str[256];
    uip_addr_networkid.value = get_ip_integeral_equivalent(network_id);
    uip_addr_iptocheck.value = get_ip_integeral_equivalent(check_ip);
    get_network_id(check_ip, mask, str);
    uip_addr_ipcheckNetworkId.value = get_ip_integeral_equivalent(str);

    return (uip_addr_ipcheckNetworkId.value == uip_addr_networkid.value);

}

uint32_t main()
{
    printf("Hello world\n");
    int8_t str[256] = "-123456789";
    printf("NUMBER IS : %d\n", get_number_from_string(str));
    int8_t ip_addr[256] = "11.1.1.0";
    int8_t weird_ip[256] = "192.168.1.13";
    printf("IP INTEGER VALUE IS : %Id\n",get_ip_integeral_equivalent(ip_addr));
    get_network_id(ip_addr,24, str);
    printf("IP NETWORK ID STRING IS %s\n", str);
    get_broadcast_address(ip_addr, 24, str);
    printf("IP BROADCAST ID IS %s\n", str);
    get_network_id(ip_addr, 24, str);
    printf("IS IP SUBNET MEMBER? %d\n", check_ip_subnet_membership(ip_addr, 24, weird_ip));
    printf("SUBNET CARDINALITY IS:%d\n", get_subnet_cardinality(24));
}