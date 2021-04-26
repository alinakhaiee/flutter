import 'package:hive/hive.dart';

part 'ClassModel.g.dart';
@HiveType(typeId : 0)
class User {
  @HiveField(0)
  String name;
  @HiveField(1)
  String password;

  User({this.password,this.name});

}



