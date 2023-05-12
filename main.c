#include "stdio.h"
#include "ip_maths.h"

int main(int argv, char **argc) {
    char ip_output[256];
    printf("arguments:%d\n", argv);
    //printf("Integer ip value : %d\n",get_ip_integeral_equivalent(argc[1]));
    //get_abcd_ip_format(202182144, ip_output);
    //printf("string ip : %s\n", ip_output);
    //get_broadcast_address("12.13.14.15", 24, ip_output);
    //printf("string broadcast addr : %s\n", ip_output);
    //printf("subnet cardinality : %d\n", get_subnet_cardinality(30));
    printf("is in net : %d\n", check_ip_subnet_membership("12.13.14.0", 24, "11.13.14.13"));
    return 0;
}