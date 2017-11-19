function webViewUrlChanged (url) {
  url = url.toString()
  if (url.indexOf('redirect_uri') !== -1) {
    return
  }

  var codeIndex = url.indexOf('code=')
  if (codeIndex === -1) {
    return
  }

  console.log(url.substring(codeIndex + 5))
  authentificated(url.substring(codeIndex + 5))
}

function authentificated (code) {
  uberWorker.sendMessage({'apiMethod': 'oauth.access', 'code': code})
}

function workerOnMessage (messageObject) {
  if (messageObject.apiMethod === 'oauth.access') {
    tokenReceived(messageObject.data.access_token)
  }
}

function tokenReceived (token) {
   console.log(token)
}
