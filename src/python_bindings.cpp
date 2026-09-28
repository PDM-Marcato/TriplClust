#include "pybind11/pybind11.h"
#include "pybind11/stl.h"   // important for std::vector conversions
#include "run_clustering.h"


using namespace std;
namespace py = pybind11;



PYBIND11_MODULE(pyTriplClust, m) {
    m.doc() = "Python bindings for triplclustlib";

        
    // Bind your main class
    py::class_<Run_clustering>(m, "Run_clustering")
        .def(py::init<>())
        .def("Init", &Run_clustering::Init)
        .def("Solve", &Run_clustering::Solve)
        .def("GetIDs", &Run_clustering::GetIDs);  // std::vector<Cluster> handled automatically
}



