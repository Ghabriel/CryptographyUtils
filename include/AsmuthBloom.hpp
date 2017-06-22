#ifndef ASMUTH_BLOOM_HPP
#define ASMUTH_BLOOM_HPP

namespace crypto {
    class AsmuthBloom {
     public:
        using PartGroup = std::vector<std::pair<Number, Number>>;

        AsmuthBloom(NumberView k, NumberView n);
        PartGroup split(NumberView secret) const;
        Number reconstruct(const PartGroup&) const;

     private:
        Number k;
        Number n;
    };
}

#endif
