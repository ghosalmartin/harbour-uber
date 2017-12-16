#ifndef ENDPOINTS_H
#define ENDPOINTS_H

#define UBER_API_VERSION = "1.2";

#ifdef QT_DEBUG
#define UBER_BASE_ENDPOINT = "https://sandbox-api.uber.com/";
#else
#define UBER_BASE_ENDPOINT = "https://api.uber.com/";
#endif

#define UBER_ENDPOINT = UBER_BASE_ENDPOINT + UBER_API_VERSION;

//Riders
#define UBER_ME_ENDPOINT = UBER_ENDPOINT + "/me";
#define UBER_HISTORY_ENDPOINT = UBER_ENDPOINT + "/history";
#define UBER_PAYMENT_METHODS_ENDPOINT = UBER_ENDPOINT + "/payment_methods";
#define UBER_PLACES_ENDPOINT = UBER_ENDPOINT + "/places/%1";

//Ride Products
#define UBER_PRODUCTS_ENDPOINT = UBER_ENDPOINT + "/products";
#define UBER_SPECIFIC_PRODUCT_ENDPOINT = UBER_ENDPOINT + "/products/%1";

//Ride Estimates
#define UBER_ESTIMATES_ENDPOINT = UBER_ENDPOINT + "/estimates";
#define UBER_ESTIMATE_PRICE_ENDPOINT = UBER_ESTIMATES_ENDPOINT + "/price";
#define UBER_ESTIMATE_TIME_ENDPOINT = UBER_ESTIMATES_ENDPOINT + "/time";

//Ride Requests
#define UBER_REQUESTS_ENDPOINT = UBER_ENDPOINT + "/requests";
#define UBER_REQUESTS_ESTIMATE_ENDPOINT = UBER_REQUESTS_ENDPOINT + "/estimate";
#define UBER_REQUESTS_CURRENT_ENDPOINT = UBER_REQUESTS_ENDPOINT + "/current";
#define UBER_REQUEST_ENDPOINT = UBER_REQUESTS_ENDPOINT + "/%1";
#define UBER_REQUEST_MAP_ENDPOINT = UBER_REQUEST_ENDPOINT + "/%1/map";
#define UBER_REQUEST_RECEIPT_ENDPOINT = UBER_REQUEST_ENDPOINT + "/%1/receipt";

#endif // ENDPOINTS_H
