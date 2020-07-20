#if !defined(TURN_NO_PROMETHEUS)

#include "mainrelay.h"
#include "prom_server.h"

int start_prometheus_server(void){
  if (turn_params.prometheus == 0){
    return 0;
  }
  prom_collector_registry_default_init();

  // Create server traffic gauge metrics
  turn_server_peer_traffic_rcvp = prom_collector_registry_must_register_metric(prom_counter_new("turn_server_peer_traffic_rcvp", "Represents total peer received packets across all allocations", 0, NULL));
  turn_server_peer_traffic_rcvb = prom_collector_registry_must_register_metric(prom_counter_new("turn_server_peer_traffic_rcvb", "Represents total peer received bytes across all allocations", 0, NULL));
  turn_server_peer_traffic_sentp = prom_collector_registry_must_register_metric(prom_counter_new("turn_server_peer_traffic_sentp", "Represents total peer sent packets across all allocations", 0, NULL));
  turn_server_peer_traffic_sentb = prom_collector_registry_must_register_metric(prom_counter_new("turn_server_peer_traffic_sentb", "Represents total peer sent bytes across all allocations", 0, NULL));

  turn_server_total_traffic_rcvp = prom_collector_registry_must_register_metric(prom_counter_new("turn_server_total_traffic_rcvp", "Represents total received packets across all allocations", 0, NULL));
  turn_server_total_traffic_rcvb = prom_collector_registry_must_register_metric(prom_counter_new("turn_server_total_traffic_rcvb", "Represents total received bytes across all allocations", 0, NULL));
  turn_server_total_traffic_sentp = prom_collector_registry_must_register_metric(prom_counter_new("turn_server_total_traffic_sentp", "Represents total sent packets across all allocations", 0, NULL));
  turn_server_total_traffic_sentb = prom_collector_registry_must_register_metric(prom_counter_new("turn_server_total_traffic_sentb", "Represents total sent bytes across all allocations", 0, NULL));

  promhttp_set_active_collector_registry(NULL);
  

  struct MHD_Daemon *daemon = promhttp_start_daemon(MHD_USE_SELECT_INTERNALLY, DEFAULT_PROM_SERVER_PORT, NULL, NULL);
  if (daemon == NULL) {
    return 1;
  }
  return 0;
}

void prom_set_traffic(unsigned long rsvp, unsigned long rsvb, unsigned long sentp, unsigned long sentb, bool peer){
  if (turn_params.prometheus == 1){
    if (peer){
      prom_counter_add(turn_server_peer_traffic_rcvp, rsvp, NULL);
      prom_counter_add(turn_server_peer_traffic_rcvb, rsvb, NULL);
      prom_counter_add(turn_server_peer_traffic_sentp, sentp, NULL);
      prom_counter_add(turn_server_peer_traffic_sentb, sentb, NULL);
    } else {
      prom_counter_add(turn_server_total_traffic_rcvp, rsvp, NULL);
      prom_counter_add(turn_server_total_traffic_rcvb, rsvb, NULL);
      prom_counter_add(turn_server_total_traffic_sentp, sentp, NULL);
      prom_counter_add(turn_server_total_traffic_sentb, sentb, NULL);
    }
  }
}

#endif /* TURN_NO_PROMETHEUS */
