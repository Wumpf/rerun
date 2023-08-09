// NOTE: This file was autogenerated by re_types_builder; DO NOT EDIT.
// Based on "crates/re_types/definitions/rerun/components/annotation_context.fbs"

#include "annotation_context.hpp"

#include "../arrow.hpp"
#include "../datatypes/class_description_map_elem.hpp"

#include <arrow/api.h>

namespace rerun {
    namespace components {
        const char *AnnotationContext::NAME = "rerun.annotation_context";

        const std::shared_ptr<arrow::DataType> &AnnotationContext::to_arrow_datatype() {
            static const auto datatype = arrow::list(arrow::field(
                "item",
                rerun::datatypes::ClassDescriptionMapElem::to_arrow_datatype(),
                false
            ));
            return datatype;
        }

        arrow::Result<std::shared_ptr<arrow::ListBuilder>>
            AnnotationContext::new_arrow_array_builder(arrow::MemoryPool *memory_pool) {
            if (!memory_pool) {
                return arrow::Status::Invalid("Memory pool is null.");
            }

            return arrow::Result(std::make_shared<arrow::ListBuilder>(
                memory_pool,
                rerun::datatypes::ClassDescriptionMapElem::new_arrow_array_builder(memory_pool)
                    .ValueOrDie()
            ));
        }

        arrow::Status AnnotationContext::fill_arrow_array_builder(
            arrow::ListBuilder *builder, const AnnotationContext *elements, size_t num_elements
        ) {
            if (!builder) {
                return arrow::Status::Invalid("Passed array builder is null.");
            }
            if (!elements) {
                return arrow::Status::Invalid("Cannot serialize null pointer to arrow array.");
            }

            auto value_builder = static_cast<arrow::StructBuilder *>(builder->value_builder());
            ARROW_RETURN_NOT_OK(builder->Reserve(num_elements));
            ARROW_RETURN_NOT_OK(value_builder->Reserve(num_elements * 2));

            for (auto elem_idx = 0; elem_idx < num_elements; elem_idx += 1) {
                const auto &element = elements[elem_idx];
                ARROW_RETURN_NOT_OK(
                    rerun::datatypes::ClassDescriptionMapElem::fill_arrow_array_builder(
                        value_builder,
                        element.class_map.data(),
                        element.class_map.size()
                    )
                );
                ARROW_RETURN_NOT_OK(builder->Append());
            }

            return arrow::Status::OK();
        }

        arrow::Result<rerun::DataCell> AnnotationContext::to_data_cell(
            const AnnotationContext *instances, size_t num_instances
        ) {
            // TODO(andreas): Allow configuring the memory pool.
            arrow::MemoryPool *pool = arrow::default_memory_pool();

            ARROW_ASSIGN_OR_RAISE(auto builder, AnnotationContext::new_arrow_array_builder(pool));
            if (instances && num_instances > 0) {
                ARROW_RETURN_NOT_OK(AnnotationContext::fill_arrow_array_builder(
                    builder.get(),
                    instances,
                    num_instances
                ));
            }
            std::shared_ptr<arrow::Array> array;
            ARROW_RETURN_NOT_OK(builder->Finish(&array));

            auto schema = arrow::schema({arrow::field(
                AnnotationContext::NAME,
                AnnotationContext::to_arrow_datatype(),
                false
            )});

            rerun::DataCell cell;
            cell.component_name = AnnotationContext::NAME;
            ARROW_ASSIGN_OR_RAISE(
                cell.buffer,
                rerun::ipc_from_table(*arrow::Table::Make(schema, {array}))
            );

            return cell;
        }
    } // namespace components
} // namespace rerun
