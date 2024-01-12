// DO NOT EDIT! This file was auto-generated by crates/re_types_builder/src/codegen/cpp/mod.rs
// Based on "crates/re_types/definitions/rerun/blueprint/components/grid_columns.fbs".

#pragma once

#include "../../result.hpp"

#include <cstdint>
#include <memory>

namespace arrow {
    /// \private
    template <typename T>
    class NumericBuilder;

    class Array;
    class DataType;
    class UInt32Type;
    using UInt32Builder = NumericBuilder<UInt32Type>;
} // namespace arrow

namespace rerun::blueprint::components {
    /// **Component**: How many columns a grid container should have.
    struct GridColumns {
        /// The number of columns.
        uint32_t columns;

      public:
        GridColumns() = default;

        GridColumns(uint32_t columns_) : columns(columns_) {}

        GridColumns& operator=(uint32_t columns_) {
            columns = columns_;
            return *this;
        }
    };
} // namespace rerun::blueprint::components

namespace rerun {
    template <typename T>
    struct Loggable;

    /// \private
    template <>
    struct Loggable<blueprint::components::GridColumns> {
        static constexpr const char Name[] = "rerun.blueprint.components.GridColumns";

        /// Returns the arrow data type this type corresponds to.
        static const std::shared_ptr<arrow::DataType>& arrow_datatype();

        /// Fills an arrow array builder with an array of this type.
        static rerun::Error fill_arrow_array_builder(
            arrow::UInt32Builder* builder, const blueprint::components::GridColumns* elements,
            size_t num_elements
        );

        /// Serializes an array of `rerun::blueprint:: components::GridColumns` into an arrow array.
        static Result<std::shared_ptr<arrow::Array>> to_arrow(
            const blueprint::components::GridColumns* instances, size_t num_instances
        );
    };
} // namespace rerun