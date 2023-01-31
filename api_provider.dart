import 'dart:async';
import 'dart:convert';
import 'dart:io';

import 'package:device_app/data/network/network.dart';
import 'package:device_app/data/network/src/connect/connect.dart';
import 'package:device_app/data/network/src/provider/return_response_model.dart';
import 'package:flutter/foundation.dart';
import 'package:http/http.dart' as http;

part 'function_repository.dart';

class ApiProvider {
  ApiProvider() {
    _onInit();
  }

  late final Connect _connect;

  void _onInit() {
    _connect = Connect();
    _connect.timeout = const Duration(seconds: 15);
    _connect.headers = {
      'Content-Type': 'application/json; charset=utf-8',
      "Accept": "application/json",
      'Access-Control-Allow-Origin': '*',
      'Access-Control-Allow-Methods': 'POST,GET,DELETE,PUT',
      'Accept-Language': 'Fa'
    };
  }

  Future<ReturnResponse> post(String url, {Map<String, dynamic>? data}) =>
      _callApi(() => _connect.post(url, body: data));

  Future<ReturnResponse> get(String url) => _callApi(() => _connect.get(url));

  Future<ReturnResponse> delete(String url, {Map<String, dynamic>? data}) =>
      _callApi(() => _connect.delete(url, body: data));

  Future<ReturnResponse> put(String url, {Map<String, dynamic>? data}) => _callApi(() => _connect.put(url, body: data));

  Future<ReturnResponse> patch(String url, {Map<String, dynamic>? data}) =>
      _callApi(() => _connect.patch(url, body: data));

  Future<ReturnResponse> download(String url, String path, {DownloadProgress? downloadProgress}) => _callApi(
      () => _connect.download(url, path, downloadProgress: downloadProgress, timeoutIn: const Duration(seconds: 60)),
      notFormatResponse: true);

  void setAuthenticator({required String url, required String refresh}) => _connect.authenticator = () async {
        try {
          final token = await _connect.post(url, body: {"refresh": refresh});
          _connect.headers['Authorization'] = "Bearer $token";
          return;
        } catch (e) {
          if (kDebugMode) {
            print(e);
          }
          return;
        }
      };

  set setToken(String token) => _connect.headers['Authorization'] = "Bearer $token";
}
