#include "util/HDF5Interface.h"

HDF5Interface::HDF5Interface(std::string filename_input, FILE_ACCESS_MODE mode_input)
    : filename(filename_input)
{
    switch_to(mode_input);
}

/* HDF5Interface:: */
/* ~HDF5Interface() */
/* { */
/*         file.reset(); */
/* } */

inline void HDF5Interface::
switch_to (FILE_ACCESS_MODE mode_input)
{
	MODE = mode_input;
	if      (MODE == WRITE) { file = std::make_unique<H5::H5File>(filename.c_str(), H5F_ACC_TRUNC); }
	else if (MODE == READ)  { file = std::make_unique<H5::H5File>(filename.c_str(), H5F_ACC_RDONLY); }
	else if (MODE == REWRITE) { file = std::make_unique<H5::H5File>(filename.c_str(), H5F_ACC_RDWR); }
}

void HDF5Interface::
close()
{
	file->close();
}

void HDF5Interface::
create_group (std::string grp_name)
{
	if (!HAS_GROUP(grp_name))
	{
		try {file->createGroup(grp_name.c_str());}
		catch(...) {}
	}
}

bool HDF5Interface::
HAS_GROUP (std::string grp_name)
{
//	bool out = true;
//	try {file->openGroup(grp_name.c_str());}
//	catch(...) {out = false;}
//	return out;
	return H5Lexists(file->getId(), grp_name.c_str(), H5P_DEFAULT) > 0;
}

std::vector<std::string> HDF5Interface::get_groups() const
{
    hsize_t nobjs = file->getNumObjs();
    std::vector<std::string> out(nobjs);

    H5std_string obj_name;
    for(std::size_t i = 0; i < nobjs; i++) { out[i] = file->getObjnameByIdx(i); }
    return out;
}

size_t HDF5Interface::get_vector_size(const char* setname)
{
    assert(MODE == READ);
    H5::DataSet dataset = file->openDataSet(setname);
    H5::DataSpace dataspace = dataset.getSpace();
    hsize_t length[1];
    dataspace.getSimpleExtentDims(length, NULL);
    return length[0];
}

void HDF5Interface::save_char(std::string salvandum, const char* setname)
{
    assert(MODE == WRITE or MODE == REWRITE);
    hsize_t length[] = {1};
    H5::DataSpace space(1, length);
    H5::StrType datatype(0, H5T_VARIABLE);
    H5::DataSet dataset = file->createDataSet(setname, datatype, space);
    const char* this_sucks_hairy_balls_but_it_works[1] = {0};
    this_sucks_hairy_balls_but_it_works[0] = salvandum.c_str();
    dataset.write((void*)this_sucks_hairy_balls_but_it_works, datatype);
}

void HDF5Interface::load_char(const char* setname, std::string& c)
{
    assert(MODE == READ);
    H5::DataSet dataset = file->openDataSet(setname);
    H5::DataType datatype = dataset.getDataType();
    // H5::DataSpace dataspace = dataset.getSpace();
    // hsize_t length[] = {1};
    // H5::DataSpace double_memspace(1,length);
    const char* this_sucks_hairy_balls_but_it_works[1] = {0};
    dataset.read((void*)this_sucks_hairy_balls_but_it_works, datatype);
    c = this_sucks_hairy_balls_but_it_works[0];
}
