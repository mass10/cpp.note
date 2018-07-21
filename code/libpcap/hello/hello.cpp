#include <stdio.h>
#include <pcap.h>

// [Programming with pcap]
// http://www.tcpdump.org/pcap.htm
//
// 日本人のブログ
// http://www.cgitest.net/memo/wiki.cgi?page=libpcap#p4
//
// http://win6.jp/memos/pcap/pcap-eztut.html
//
//
//
//
//
//
//
//

int main(int argc, char* argv[]) {

	char *dev, errbuf[PCAP_ERRBUF_SIZE + 10];

	dev = pcap_lookupdev(errbuf);
	if(dev == NULL) {
		fprintf(stderr, "[ERROR] Couldn't find default device: [%s]\n", errbuf);
		return(2);
	}
	printf("Device: %s\n", dev);
	return(0);
}
