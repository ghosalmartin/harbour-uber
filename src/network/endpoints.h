#ifndef ENDPOINTS_H
#define ENDPOINTS_H

const char UBER_API_VERSION[] = "1.2";

#ifdef QT_DEBUG
const char UBER_BASE_ENDPOINT[] = "https://sandbox-api.uber.com/";
#else
const char UBER_BASE_ENDPOINT[] = "https://api.uber.com/";
#endif

const char UBER_ENDPOINT[] = UBER_BASE_ENDPOINT + UBER_API_VERSION;

//Riders
const char UBER_ME_ENDPOINT[] = UBER_ENDPOINT + "/me";
const char UBER_HISTORY_ENDPOINT[] = UBER_ENDPOINT + "/history";
const char UBER_PAYMENT_METHODS_ENDPOINT[] = UBER_ENDPOINT + "/payment_methods";
const char UBER_PLACES_ENDPOINT[] = UBER_ENDPOINT + "/places/%1";

//Ride Products
const char UBER_PRODUCTS_ENDPOINT[] = UBER_ENDPOINT + "/products";
const char UBER_SPECIFIC_PRODUCT_ENDPOINT[] = UBER_ENDPOINT + "/products/%1";

//Ride Estimates
const char UBER_ESTIMATES_ENDPOINT[] = UBER_ENDPOINT + "/estimates";
const char UBER_ESTIMATE_PRICE_ENDPOINT[] = UBER_ESTIMATES_ENDPOINT + "/price";
const char UBER_ESTIMATE_TIME_ENDPOINT[] = UBER_ESTIMATES_ENDPOINT + "/time";

//Ride Requests
const char UBER_REQUESTS_ENDPOINT[] = UBER_ENDPOINT + "/requests";
const char UBER_REQUESTS_ESTIMATE_ENDPOINT[] = UBER_REQUESTS_ENDPOINT + "/estimate";
const char UBER_REQUESTS_CURRENT_ENDPOINT[] = UBER_REQUESTS_ENDPOINT + "/current";
const char UBER_REQUEST_ENDPOINT[] = UBER_REQUESTS_ENDPOINT + "/%1";
const char UBER_REQUEST_MAP_ENDPOINT[] = UBER_REQUEST_ENDPOINT + "/%1/map";
const char UBER_REQUEST_RECEIPT_ENDPOINT[] = UBER_REQUEST_ENDPOINT + "/%1/receipt";

#endif // ENDPOINTS_H
