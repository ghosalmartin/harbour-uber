/* attributes */
var baseUrl = 'https://login.uber.com/oauth/v2/token'
var clientID = 'z2hUEP5mar6x466S6JoVqjOFLQA5yei3'
var clientSecret = 'bX4Zy0RzGxPAklazjPLgyouiktUHM1sKQ36q6eZ_'
var redirectUri = 'https%3A%2F%2Flocalhost%3A8888'
var grantType = 'authorization_code'
var scope = 'ride_widgets'

/* Distributes calls of Uber API functions */
WorkerScript.onMessage = function (data) {
  console.log('workerScript onMessage:', JSON.stringify(data))
  if (data.apiMethod === 'oauth.access') {
    oauthAccessRequest(data.code)
  } else {
    console.log('Unknown request to workerScript')
  }
}

function oauthAccessRequest (code) {
  var endpoint = baseUrl +
  '?client_id=' + clientID +
  '&client_secret=' + clientSecret +
  '&grant_type=' + grantType +
  '&redirect_uri=' + redirectUri +
  '&code=' + code +
  '&scope=' + scope
  httpPost(endpoint)
}

function httpPost (endpoint) {
  var http = new XMLHttpRequest()

  http.onreadystatechange = function () {
    if (http.readyState === XMLHttpRequest.DONE) {
      if(http.status === 200) {
        WorkerScript.sendMessage({ 'status': 'done', 'data': JSON.parse(http.responseText), 'apiMethod': 'oauth.access' })
      } else {
        WorkerScript.sendMessage({ 'status': 'error', 'data': null, 'apiMethod': 'none' })
      }
    }
  }

  http.open('POST', endpoint)
  http.send()
}
