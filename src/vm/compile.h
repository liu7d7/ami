#pragma once

#include "vm.h"
#include "../parse.h"

namespace tosuto::vm {
  struct local {
    value::str name{""};
    u8 depth{};

    inline local(value::str&& name, u8 depth) : name(name), depth(depth) {}

    constexpr static u8 invalid_depth = std::numeric_limits<u8>::max();
  };

  struct compiler {
    chunk ch;
    constexpr static u16 max_locals = std::numeric_limits<u16>::max();
    std::vector<local> locals;
    u8 depth{};

    std::expected<void, std::string> number(node* n);

    std::expected<void, std::string> bin_op(node* n);
    std::expected<void, std::string> un_op(node* n);

    std::expected<void, std::string> block(node* n);

    std::expected<void, std::string> compile(node* n);

    std::expected<void, std::string> kw_literal(node* n);

    std::expected<void, std::string> string(node* n);

    std::expected<void, std::string> var_def(node* n);

    std::expected<void, std::string> field_get(node* n);

    std::expected<void, std::string> add_local(const std::string& name);

    void begin_block();

    void end_block();

    std::optional<u16> resolve_local(std::string const& name);

    std::expected<void, std::string> if_stmt(node* n);

    size_t emit_jump(op_code type);

    std::expected<void, std::string> patch_jump(size_t offset);

    std::expected<void, std::string> global(node* n);
  };
}