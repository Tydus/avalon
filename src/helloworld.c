#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <stdarg.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void fail(const char *fmt, ...){
    va_list vl;
    va_start(vl,fmt);
    vfprintf(stderr,fmt,vl);
    exit(-1);
}

int main(int argc, char *argv[]){
    char errbuf[PCAP_ERRBUF_SIZE];
    int ret;

    //char *dev=pcap_lookupdev(errbuf);
    const char *dev=argv[1];
    if(!dev)
        fail("no dev\n",errbuf);
    printf("DEV: %s\n",dev);

    bpf_u_int32 netp,maskp;
    ret=pcap_lookupnet(dev,&netp,&maskp,errbuf);
    if(ret==-1)
        fail("%s\n",errbuf);

    struct in_addr addr;
    addr.s_addr=netp;
    const char *net=inet_ntoa(addr);
    if(!net)
        fail("ntoa\n");
    printf("NET: %s\n",net);

    addr.s_addr=maskp;
    net=inet_ntoa(addr);
    if(!net)
        fail("ntoa\n");
    printf("NET: %s\n",net);

    return 0;
}

