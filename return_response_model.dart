
import 'package:http/http.dart' as http;
enum StatusType { success, noContent, error, connectionError, unAuthorized, cancel }

class ReturnResponse {
  String? message;
  int? statusCode;
  dynamic payLoad;
  late StatusType? statusType;

  ReturnResponse({
    this.message,
    this.statusCode,
    this.payLoad,
    this.statusType,
  });

  factory ReturnResponse.fromJson(dynamic res) {
    String? message;
    try {
      message = res["payload"]["detail"][0];
    } catch (e) {
      message = res["message"];
    }
    return ReturnResponse(
      message: message,
      statusCode: res["status_code"],
      payLoad: res["payload"],
    );
  }

  Map<String, dynamic> toJson() {
    return {"message": message, "statusCode": statusCode, "payLoad": payLoad};
  }

  factory ReturnResponse.fromJson2(http.Response res) {
    return ReturnResponse(
      message:res.reasonPhrase,
      statusCode: res.statusCode,
      payLoad: res.body,
    );
  }

  ReturnResponse copyWith({String? message, int? statusCode, dynamic payLoad, StatusType? statusType}) {
    return ReturnResponse(
      statusCode: statusCode ?? this.statusCode,
      message: message ?? this.message,
      payLoad: payLoad ?? this.payLoad,
      statusType: statusType ?? this.statusType,
    );
  }
}
