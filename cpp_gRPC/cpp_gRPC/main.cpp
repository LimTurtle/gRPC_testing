#include <iostream>
#include <fstream>
#include <string>
#include "tutorial.pb.h"
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
using namespace std;
using namespace google;

int main(int argc, char* argv[]) {
	Person src_person;
	src_person.set_id(41);
	src_person.set_name("alice");
	src_person.set_email("alice@anydomain.com");


	int buf_size = src_person.ByteSizeLong();
	char* output_buf = new char[buf_size];
	protobuf::io::ArrayOutputStream os(output_buf, buf_size);
	src_person.SerializeToZeroCopyStream(&os);

	protobuf::io::ArrayInputStream is(output_buf, buf_size);
	Person dst_person0;
	dst_person0.ParseFromZeroCopyStream(&is);

	string name = dst_person0.name();
	int id = dst_person0.id();
	
	cout << name << " / " << id << endl;

	const char* test_filename = "person.txt";
	fstream ofs(test_filename, ios::out | ios::trunc | ios::binary);
	src_person.SerializeToOstream(&ofs);
	ofs.close();

	fstream ifs(test_filename, ios::in | ios::binary);
	Person dst_person1;
	dst_person1.ParseFromIstream(&ifs);
	cout << dst_person1.id() << " / " << dst_person1.name() << endl;
	ifs.close();

	delete[] output_buf;
	output_buf = NULL;
	protobuf::ShutdownProtobufLibrary();
	return 0;
}