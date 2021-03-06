#include <libpull/security/sha256.h>
#include "libpull_agents/update.h"

#include "support/support.h"

#include <unistd.h>

#define TIMEOUT 1000
#define BUFFER_SIZE 1024

static agent_msg_t agent_msg;
static update_agent_config cfg;
static update_agent_ctx_t ctx;
static int8_t retries = 3;
static uint8_t success = 0;
static uint8_t buffer[BUFFER_SIZE];

void ntest_prepare(void) {
    bzero(&cfg, sizeof(cfg));
    bzero(&ctx, sizeof(ctx));
    retries = 3;
    success = 0;
}

void ntest_clean(void) { 
    restore_assets();
}

void update_runner(conn_type type, void* data) {
    conn_config(&cfg.subscriber, "localhost", 0, type, data, "version");
    conn_config(&cfg.receiver, "localhost", 0, type, data, "firmware");
    update_agent_reuse_connection(&cfg, 0);
    update_agent_set_identity(&cfg, identity_g);
    update_agent_vendor_keys(&cfg, (uint8_t*) vendor_x_g, (uint8_t*) vendor_y_g);
    update_agent_digest_func(&cfg, tinydtls_digest_sha256);
    update_agent_ecc_func(&cfg, tinydtls_secp256r1_ecc);
    update_agent_set_buffer(&cfg, buffer, BUFFER_SIZE);

    while (1) {
        agent_msg = update_agent(&cfg, &ctx);
        if (IS_FAILURE(agent_msg)) {
            break;
        } else if (IS_CONTINUE(agent_msg)) {
            if (agent_msg.event == EVENT_APPLY) {
                success = 1;
                break;
            }
        } else if (IS_RECOVER(agent_msg)) {
            if (retries-- <= 0) {
                continue;
            } else {
                break;
            }
        } else if (IS_SEND(agent_msg)) {
            loop(GET_CONNECTION(agent_msg), TIMEOUT);
        }
    }
    nTEST_TRUE(success, "There was an error during the update phase\n");
}

void test_update_success(void) {
    update_runner(PULL_UDP, NULL);
}

void test_update_success_dtls(void) {
    static dtls_ecdh_data_t ecdh_data = {
         .priv_key = (uint8_t*) dtls_client_priv_g,
         .pub_key_x = (uint8_t*) dtls_client_x_g,
         .pub_key_y = (uint8_t*) dtls_client_y_g
    };
    update_runner(PULL_DTLS_ECDH, &ecdh_data);
}

int main() {
    nTEST_INIT();
    nTEST_RUN(test_update_success);
    nTEST_RUN(test_update_success_dtls);
    nTEST_END();
    nTEST_RETURN();
}
