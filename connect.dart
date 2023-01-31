import 'dart:async';
import 'dart:convert';
import 'dart:io';
import 'dart:typed_data';

import 'package:http/http.dart' as http;

typedef Authenticator = Future Function();
typedef DownloadProgress = void Function(int total, int download, double progress);

class Connect {
  final http.Client _inner = http.Client();
  Authenticator? authenticator;
  Map<String, String> headers = {};
  Duration timeout = const Duration(milliseconds: 10);

  Future<http.Response> get(String url, {Duration? timeoutIn, Map<String, String>? headersIn}) =>
      _provider(() => _inner.get(Uri.parse(url), headers: _headers(headersIn)).timeout(_timeout(timeoutIn)));

  Future<http.Response> post(String url,
          {Object? body, Encoding? encoding, Duration? timeoutIn, Map<String, String>? headersIn}) =>
      _provider(() => _inner
          .post(Uri.parse(url), body: jsonEncode(body), encoding: encoding, headers: _headers(headersIn))
          .timeout(_timeout(timeoutIn)));

  Future<http.Response> put(String url,
          {Object? body, Encoding? encoding, Duration? timeoutIn, Map<String, String>? headersIn}) =>
      _provider(() => _inner
          .put(Uri.parse(url), body: jsonEncode(body), encoding: encoding, headers: _headers(headersIn))
          .timeout(_timeout(timeoutIn)));

  Future<http.Response> patch(String url,
          {Object? body, Encoding? encoding, Duration? timeoutIn, Map<String, String>? headersIn}) =>
      _provider(() => _inner
          .patch(Uri.parse(url), body: jsonEncode(body), encoding: encoding, headers: _headers(headersIn))
          .timeout(_timeout(timeoutIn)));

  Future<http.Response> delete(String url,
          {Object? body, Encoding? encoding, Duration? timeoutIn, Map<String, String>? headersIn}) =>
      _provider(() => _inner
          .delete(Uri.parse(url), body: jsonEncode(body), encoding: encoding, headers: _headers(headersIn))
          .timeout(_timeout(timeoutIn)));

  Future<http.Response> download(String url, String path,
      {Duration? timeoutIn, Map<String, String>? headersIn, DownloadProgress? downloadProgress}) async {
    Completer<http.Response> completer = Completer();
    final request = http.Request('GET', Uri.parse(url));
    late http.Response result;
    final response = _inner.send(request).timeout(_timeout(timeoutIn));
    int downloadedBytes = 0;
    List<List<int>> chunkList = [];
    response.asStream().listen((http.StreamedResponse streamedResponse) {
      streamedResponse.stream.listen((chunk) {
        final contentLength = streamedResponse.contentLength ?? 0;
        final progress = (downloadedBytes / contentLength) * 100;
        downloadProgress?.call(contentLength, downloadedBytes, progress);
        chunkList.add(chunk);
        downloadedBytes += chunk.length;
      }, onDone: () async {
        final contentLength = streamedResponse.contentLength ?? 0;
        final progress = (downloadedBytes / contentLength) * 100;
        downloadProgress?.call(contentLength, downloadedBytes, progress);
        int start = 0;
        final bytes = Uint8List(contentLength);

        for (var chunk in chunkList) {
          bytes.setRange(start, start + chunk.length, chunk);
          start += chunk.length;
        }
        await File(path).writeAsBytes(bytes);
        result = http.Response.bytes(
          bytes,
          streamedResponse.statusCode,
          request: streamedResponse.request,
          headers: streamedResponse.headers,
          isRedirect: streamedResponse.isRedirect,
          persistentConnection: streamedResponse.persistentConnection,
          reasonPhrase: streamedResponse.reasonPhrase,
        );
        completer.complete(result);
        return;
      }, onError: (e) {
        completer.completeError(e);
      });
    });
    return completer.future;
  }

  Future<http.Response> _provider(Future<http.Response> Function() api, {bool authenticate = false}) async {
    if (authenticate) {
      await authenticator?.call();
    }
    final res = await api();
    if (res.statusCode == 401) {
      _provider(api, authenticate: true);
    }
    return res;
  }

  Map<String, String> _headers(Map<String, String>? head) {
    return {...headers, ...?head};
  }

  Duration _timeout(Duration? duration) {
    return duration ?? timeout;
  }
}
