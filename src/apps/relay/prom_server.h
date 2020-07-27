
#ifndef __PROM_SERVER_H__
#define __PROM_SERVER_H__

#if !defined(TURN_NO_PROMETHEUS)

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include <microhttpd.h>
#include <prom.h>
#include <promhttp.h>

#define DEFAULT_PROM_SERVER_PORT (9121)

prom_counter_t *turn_server_peer_traffic_rcvp;
prom_counter_t *turn_server_peer_traffic_rcvb;
prom_counter_t *turn_server_peer_traffic_sentp;
prom_counter_t *turn_server_peer_traffic_sentb;

prom_counter_t *turn_server_total_traffic_rcvp;
prom_counter_t *turn_server_total_traffic_rcvb;
prom_counter_t *turn_server_total_traffic_sentp;
prom_counter_t *turn_server_total_traffic_sentb;

prom_gauge_t *turn_server_allocation_count;

#ifdef __cplusplus
extern "C" {
#endif


int start_prometheus_server(void);

void prom_set_traffic(unsigned long rsvp, unsigned long rsvb, unsigned long sentp, unsigned long sentb, bool peer);

void prom_set_allocation(bool refresh);
void prom_delete_allocation(void);

#endif /* TURN_NO_PROMETHEUS */

#ifdef __cplusplus
}
#endif /* __clplusplus */

#endif /* __PROM_SERVER_H__ */