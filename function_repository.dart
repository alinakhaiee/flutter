part of 'api_provider.dart';

Future<ReturnResponse> _callApi(Future<http.Response> Function() call, {bool notFormatResponse = false}) async {
  http.Response? res;
  try {
    res = await call();
    if (kDebugMode) {
      print("request=>${res.request?.url}");
      print("token=>${res.request?.headers["Authorization"]}");
      print(
          "response=>${notFormatResponse ? "contentLength(${res.contentLength}) " : jsonDecode(utf8.decode(res.bodyBytes))}");
      print("statusCode=>${res.statusCode}");
    }
    ReturnResponse responseModel;
    if (notFormatResponse) {
      responseModel = ReturnResponse.fromJson2(res);
    } else {
      responseModel = ReturnResponse.fromJson(jsonDecode(utf8.decode(res.bodyBytes)));
    }
    responseModel.statusType = responseModel.statusCode.toStatusType;
    return responseModel;
  } catch (e) {
    if (kDebugMode) {
      print("errorCatch=>$e");
    }
    if (e is TimeoutException || e is SocketException) {
      return ReturnResponse(statusType: StatusType.connectionError, message: 'connectionError');
    }
    return ReturnResponse(statusType: StatusType.error, message: 'serverError');
  }
}
extension on int? {
  StatusType get toStatusType {
    switch (this) {
      case 200:
      case 201:
      case 202:
        return StatusType.success;
      case 204:
        return StatusType.noContent;
      case 401:
        return StatusType.unAuthorized;
      default:
        return StatusType.error;
    }
  }
}
