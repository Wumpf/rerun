// NOTE: This file was autogenerated by re_types_builder; DO NOT EDIT.
// Based on "crates/re_types/definitions/rerun/datatypes/annotation_info.fbs"

#include "annotation_info.hpp"

#include "../components/color.hpp"
#include "../components/label.hpp"

#include <arrow/api.h>

namespace rerun {
    namespace datatypes {
        const std::shared_ptr<arrow::DataType> &AnnotationInfo::to_arrow_datatype() {
            static const auto datatype = arrow::struct_({
                arrow::field("id", arrow::uint16(), false),
                arrow::field("label", rerun::components::Label::to_arrow_datatype(), true),
                arrow::field("color", rerun::components::Color::to_arrow_datatype(), true),
            });
            return datatype;
        }

        arrow::Result<std::shared_ptr<arrow::StructBuilder>>
            AnnotationInfo::new_arrow_array_builder(arrow::MemoryPool *memory_pool) {
            if (!memory_pool) {
                return arrow::Status::Invalid("Memory pool is null.");
            }

            return arrow::Result(std::make_shared<arrow::StructBuilder>(
                to_arrow_datatype(),
                memory_pool,
                std::vector<std::shared_ptr<arrow::ArrayBuilder>>({
                    std::make_shared<arrow::UInt16Builder>(memory_pool),
                    rerun::components::Label::new_arrow_array_builder(memory_pool).ValueOrDie(),
                    rerun::components::Color::new_arrow_array_builder(memory_pool).ValueOrDie(),
                })
            ));
        }

        arrow::Status AnnotationInfo::fill_arrow_array_builder(
            arrow::StructBuilder *builder, const AnnotationInfo *elements, size_t num_elements
        ) {
            if (!builder) {
                return arrow::Status::Invalid("Passed array builder is null.");
            }
            if (!elements) {
                return arrow::Status::Invalid("Cannot serialize null pointer to arrow array.");
            }

            {
                auto field_builder = static_cast<arrow::UInt16Builder *>(builder->field_builder(0));
                ARROW_RETURN_NOT_OK(field_builder->Reserve(num_elements));
                for (auto elem_idx = 0; elem_idx < num_elements; elem_idx += 1) {
                    ARROW_RETURN_NOT_OK(field_builder->Append(elements[elem_idx].id));
                }
            }
            {
                auto field_builder = static_cast<arrow::StringBuilder *>(builder->field_builder(1));
                ARROW_RETURN_NOT_OK(field_builder->Reserve(num_elements));
                for (auto elem_idx = 0; elem_idx < num_elements; elem_idx += 1) {
                    const auto &element = elements[elem_idx];
                    if (element.label.has_value()) {
                        ARROW_RETURN_NOT_OK(rerun::components::Label::fill_arrow_array_builder(
                            field_builder,
                            &element.label.value(),
                            1
                        ));
                    } else {
                        ARROW_RETURN_NOT_OK(field_builder->AppendNull());
                    }
                }
            }
            {
                auto field_builder = static_cast<arrow::UInt32Builder *>(builder->field_builder(2));
                ARROW_RETURN_NOT_OK(field_builder->Reserve(num_elements));
                for (auto elem_idx = 0; elem_idx < num_elements; elem_idx += 1) {
                    const auto &element = elements[elem_idx];
                    if (element.color.has_value()) {
                        ARROW_RETURN_NOT_OK(rerun::components::Color::fill_arrow_array_builder(
                            field_builder,
                            &element.color.value(),
                            1
                        ));
                    } else {
                        ARROW_RETURN_NOT_OK(field_builder->AppendNull());
                    }
                }
            }
            ARROW_RETURN_NOT_OK(builder->AppendValues(num_elements, nullptr));

            return arrow::Status::OK();
        }
    } // namespace datatypes
} // namespace rerun
