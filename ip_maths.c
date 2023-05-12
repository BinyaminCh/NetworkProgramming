#include "stdio.h"
#include "ip_maths.h"
// Calculate broadcast address
// Input : ip address string, mask
// Output - broadcast address string
void get_broadcast_address(char *ip_addr, char mask, char *output_buffer) {
    // 1.Obtain network id
    char networkIdStr[256];
    memset(&networkIdStr, 0, sizeof(networkIdStr));

    get_network_id(ip_addr, mask, networkIdStr);
    // 2.Find complement of mask
    unsigned int mask_bin_num = 0;
    int i = 0;
    for ( int i = 0 ; i < mask ; ++i) {
        mask_bin_num += 1;
        mask_bin_num <<= 1;
    }
    mask_bin_num <<= (32 - mask - 1);
    unsigned int maskComp = ~mask_bin_num;
    // 3.Perform binary OR of network id and mask complement
    //202182144
    unsigned long res = maskComp | get_ip_integeral_equivalent(networkIdStr);
    // 4.Convert to decimal
    // 5.Convert to string
    //202182399
    get_abcd_ip_format(res, output_buffer);
    // 6.Return value
}

int is_digit(char c) {
    if (c >= '0' && c <= '9') return 1;
    return 0;
}
// Calculate ip integeral value
// Receive ip address string, return ip integeral value
unsigned int get_ip_integeral_equivalent(char *ip_address) {
    int int_ip_value = 0;
    int num = 0;
    int oct_num = 0;
    unsigned int multiplier = 256 * 256 * 256;

    while (*ip_address != '\0') {
        if(is_digit(*ip_address)) {
            num = *ip_address - '0';
            if((*(ip_address+3)) == '.' || (*(ip_address+3)) == '\0' ){
                num *= 100;
            } else if(*(ip_address+2) == '.' || (*(ip_address+2)) == '\0') {
                num *= 10;
            } else if(*(ip_address+1) == '.' || (*(ip_address+1)) == '\0') {
                num *= 1;
            }
            oct_num += num;
        } else if(*ip_address == '.' || *ip_address == '\0'){
            num = 0;
            int_ip_value += multiplier * oct_num;
            multiplier /= 256;
            oct_num = 0;
        } else {
            printf("INVALID INPUT!");
            int_ip_value = 0;
            break;
        }
        ip_address++;
    }

    int_ip_value += multiplier * oct_num;
    return int_ip_value;
}

// Calculate ip string from ip integer value
void get_abcd_ip_format(unsigned int ip_address, char *output_buffer){
    int binaryNum[32];
    memset(&binaryNum, 0, sizeof(binaryNum));
    int i = 0;
    unsigned int multiplier = 1 << 7;
    unsigned int temp_multiplier = multiplier;
    int num = 0;
    int index = 0;
    while(ip_address > 0) {
        binaryNum[i++] = ip_address % 2;
        ip_address /= 2;
    }

    for(int i = 32 - 1 ; i >= 24 ; --i) 
    {
        num += (binaryNum[i] * temp_multiplier);
        temp_multiplier >>= 1;
    }

    if( num > 0) 
    {
        int temp_num = num;
        while(num > 0)
        {
            if(num > 100) 
            {
                output_buffer[index++] = (char)((temp_num / 100) %10 + '0');
            } 
            else if (num > 10) 
            {
                output_buffer[index++] = (char)((temp_num / 10) %10 + '0');
            } 
            else if (num > 0)
            {
                output_buffer[index++] = (char)(temp_num %10 + '0');
            }
            num /= 10;
        }
    }
    else
    {
        output_buffer[index++] = '0';
    }

temp_multiplier = multiplier;
output_buffer[index++] = '.';
        for(int i = 24 - 1 ; i >= 16 ; --i) 
    {
        num += (binaryNum[i] * temp_multiplier);
        temp_multiplier >>= 1;
    }
    temp_multiplier = multiplier;
    if( num > 0) 
    {
        int temp_num = num;
        while(num > 0)
        {
            if(num > 100) 
            {
                output_buffer[index++] = (char)((temp_num / 100) %10 + '0');
            } 
            else if (num > 10) 
            {
                output_buffer[index++] = (char)((temp_num / 10) %10 + '0');
            } 
            else if (num > 0)
            {
                output_buffer[index++] = (char)(temp_num %10 + '0');
            }
            num /= 10;
        }
    }
    else
    {
        output_buffer[index++] = '0';
    }
output_buffer[index++] = '.';
temp_multiplier = multiplier;
    for(int i = 16 - 1 ; i >= 8 ; --i) 
    {
        num += (binaryNum[i] * temp_multiplier);
        temp_multiplier >>= 1;
    }

    if( num > 0) 
    {
        int temp_num = num;
        while(num > 0)
        {
            if(num > 100) 
            {
                output_buffer[index++] = (char)((temp_num / 100) %10 + '0');
            } 
            else if (num > 10) 
            {
                output_buffer[index++] = (char)((temp_num / 10) %10 + '0');
            } 
            else if (num > 0)
            {
                output_buffer[index++] = (char)(temp_num %10 + '0');
            }
            num /= 10;
        }
    }
    else
    {
        output_buffer[index++] = '0';
    }
output_buffer[index++] = '.';
temp_multiplier = multiplier;
        for(int i = 8 - 1 ; i >= 0 ; --i) 
    {
        num += (binaryNum[i] * temp_multiplier);
        temp_multiplier >>= 1;
    }
temp_multiplier = multiplier;
    if( num > 0) 
    {
        int temp_num = num;
        while(num > 0)
        {
            if(num > 100) 
            {
                output_buffer[index++] = (char)((temp_num / 100) %10 + '0');
            } 
            else if (num > 10) 
            {
                output_buffer[index++] = (char)((temp_num / 10) %10 + '0');
            } 
            else if (num > 0)
            {
                output_buffer[index++] = (char)(temp_num %10 + '0');
            }
            num /= 10;
        }
    }
    else
    {
        output_buffer[index++] = '0';
    }

    output_buffer[index++] = '\0';

    
}
// Calculate network id from ip address string and mask
void get_network_id(char *ip_addr, char mask, char *output_buffer) {
    // 1.Represent ip_addr in binary form
    unsigned long int_ip_addr = get_ip_integeral_equivalent(ip_addr);
    // 2.Create a binary number such that first n-mask bits are all 1, remaining are 0
    unsigned long mask_bin_num = 0;
    int i = 0;
    for ( int i = 0 ; i < mask ; ++i) {
        mask_bin_num += 1;
        mask_bin_num <<= 1;
    }
    mask_bin_num <<= (32 - mask - 1);
    // 3.Perform binary AND of number from step 1 and number from step 2
    int_ip_addr = int_ip_addr & mask_bin_num;
    // 4.Convert to string
    get_abcd_ip_format(int_ip_addr, output_buffer);
}
// Calculate subnet cardinality from mask value
unsigned int get_subnet_cardinality(char mask) {
    // Maximum number of assignable ip addresses
    unsigned int mask_bin_num = 0;
    int i = 0;
    for ( int i = 0 ; i < mask ; ++i) {
        mask_bin_num += 1;
        mask_bin_num <<= 1;
    }
    mask_bin_num <<= (32 - mask - 1);
    unsigned int maskComp = ~mask_bin_num;

    return maskComp - 1;
}
// Check if ip address is member in subnet with specific network id and mask value
// Return 0 if true, else -1
int check_ip_subnet_membership(char *network_id, char mask, char *check_ip) {
    unsigned int networkId = get_ip_integeral_equivalent(network_id);
    unsigned int ipToCheck = get_ip_integeral_equivalent(check_ip);

    char newNetworkIdStr[256];
    memset(&newNetworkIdStr, 0, sizeof(newNetworkIdStr));
    get_network_id(check_ip, mask, newNetworkIdStr);
    unsigned int newNetworkIp = get_ip_integeral_equivalent(newNetworkIdStr);


    if(newNetworkIp == networkId) {
        return 0;
    }

    return 1;
}
