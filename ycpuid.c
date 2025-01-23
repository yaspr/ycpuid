//Example of how to use CPUID to extract CPU features
#include <stdio.h>
#include <cpuid.h>
#include <stdint.h>

const char logo[] =
  " __   __  _______  _______  __   __  ___   ______ \n" 
  "|  | |  ||       ||       ||  | |  ||   | |      |\n" 
  "|  |_|  ||       ||    _  ||  | |  ||   | |  _    |\n"
  "|       ||       ||   |_| ||  |_|  ||   | | | |   |\n"
  "|_     _||      _||    ___||       ||   | | |_|   |\n"
  "  |   |  |     |_ |   |    |       ||   | |       |\n"
  "  |___|  |_______||___|    |_______||___| |______|\n\n";

int main(void)
{
  printf("%s\tycpuid - version 1.0 - 2014\n", logo);
  
  {
    union {
      
      char text[16];
      uint32_t reg[4];
      
    } vendor = {.text = {0}};
    
    uint32_t idmax = 0;
    
    __cpuid(0, idmax, vendor.reg[0], vendor.reg[2], vendor.reg[1]);
    
    printf("\n%s %d 0x%x\n\n", vendor.text, idmax, idmax);
  }
  
  {
    union {
      struct {
        uint8_t step   : 4;
        uint8_t model  : 4;
        uint8_t family : 4;
        uint8_t type   : 2;
        uint8_t pad1   : 2;
        uint8_t emodel : 4;
        uint8_t efamily: 8;
        uint8_t pad2   : 4;
      };
      
      uint32_t reg;
      
    } eax = { .reg = 1 };
    
    union {
      struct {
        uint8_t fpu      : 1;
        uint8_t vme      : 1;
        uint8_t de       : 1;
        uint8_t pse      : 1;
        uint8_t tsc      : 1;
        uint8_t msr      : 1;
        uint8_t pae      : 1;
        uint8_t mce      : 1;
        uint8_t cx8      : 1;
        uint8_t apic     : 1;
        uint8_t reserved1: 1;
        uint8_t sep      : 1;
        uint8_t mtrr     : 1;
        uint8_t pge      : 1;
        uint8_t mca      : 1;
        uint8_t cmov     : 1;
        uint8_t pat      : 1;
        uint8_t pse36    : 1;
        uint8_t psn      : 1;
        uint8_t clfsh    : 1;
        uint8_t reserved2: 1;
        uint8_t ds       : 1;
        uint8_t acpi     : 1;
        uint8_t mmx      : 1;
        uint8_t fxsr     : 1;
        uint8_t sse      : 1;
        uint8_t sse2     : 1;
        uint8_t ss       : 1;
        uint8_t htt      : 1;
        uint8_t tm       : 1;
        uint8_t ia64     : 1;
        uint8_t pbe      : 1;
      };
      
      uint32_t reg;
      
    } edx = { .reg = 0 };
    
    union {
      struct {
        uint32_t sse3      : 1;
        uint32_t pclmulqdq : 1;
        uint32_t dtes64    : 1;
        uint32_t monitor   : 1;
        uint32_t dscpl     : 1;
        uint32_t vmx       : 1;
        uint32_t smx       : 1;
        uint32_t est       : 1;
        uint32_t tm2       : 1;
        uint32_t ssse3     : 1;
        uint32_t cntxid    : 1;
        uint32_t sdbg      : 1;
        uint32_t fma       : 1;
        uint32_t cx16      : 1;
        uint32_t xtpr      : 1;
        uint32_t pdcm      : 1;
        uint32_t reserved1 : 1;
        uint32_t pcid      : 1;
        uint32_t dca       : 1;
        uint32_t sse41     : 1;
        uint32_t sse42     : 1;
        uint32_t x2apic    : 1;
        uint32_t movbe     : 1;
        uint32_t popcnt    : 1;
        uint32_t tscdadline: 1;
        uint32_t aes       : 1;
        uint32_t xsave     : 1;
        uint32_t osxsave   : 1;
        uint32_t avx       : 1;
        uint32_t f16c      : 1;
        uint32_t rdrnd     : 1;
        uint32_t hypervisor: 1;      
      };
      
      uint32_t reg;
      
    } ecx = { .reg = 0 };
    
    uint32_t ebx = 0;
    
    __cpuid(1, eax.reg, ebx, ecx.reg, edx.reg);

    int model = (eax.family == 6 || eax.family == 15 ? eax.emodel << 4 : 0) + eax.model;
    int family = eax.family == 15 ? eax.efamily : eax.family;
    
    printf("step      :\t%d\t0x%x\n"
	   "model     :\t%d\t0x%x \n"
	   "family    :\t%d\t0x%x\n"
	   "type      :\t%d\t0x%x\n\n", 
           eax.step, eax.step,
	   model, model,
	   family, family,
	   eax.type, eax.type);

    printf("fpu       :\t%d\n"
	   "mmx       :\t%d\n"
	   "sse       :\t%d\n"
	   "sse2      :\t%d\n"
	   "htt       :\t%d\n"
	   "ia64      :\t%d\n\n",
           edx.fpu, edx.mmx, edx.sse, edx.sse2, edx.htt, edx.ia64);

    printf("sse3      :\t%d\n"
	   "vmx       :\t%d\n"
	   "ssse3     :\t%d\n"
	   "fma       :\t%d\n"
	   "sse41     :\t%d\n"
	   "sse42     :\t%d\n"
	   "popcnt    :\t%d\n"
	   "aes       :\t%d\n"
	   "avx       :\t%d\n"
	   "hypervisor:\t%d (useful for detecting if running in a VM)\n\n",
           ecx.sse3, ecx.vmx, ecx.ssse3, ecx.fma, ecx.sse41, ecx.sse42,
           ecx.popcnt, ecx.aes, ecx.avx, ecx.hypervisor);
  }
  
  {
    union {
      struct {
        uint8_t fsgsbase         : 1;
        uint8_t ia32tscadjust    : 1;
        uint8_t sgx              : 1;
        uint8_t bmi1             : 1;
        uint8_t hle              : 1;
        uint8_t avx2             : 1;
        uint8_t reserved1        : 1;
        uint8_t smep             : 1;
        uint8_t bmi2             : 1;
        uint8_t erms             : 1;
        uint8_t invpcid          : 1;
        uint8_t rtm              : 1;
        uint8_t pqm              : 1;
        uint8_t fpucsdsdeprecated: 1;
        uint8_t mpx              : 1;
        uint8_t pqe              : 1;
        uint8_t avx512f          : 1;
        uint8_t avx512dq         : 1;
        uint8_t rdseed           : 1;
        uint8_t adx              : 1;
        uint8_t smap             : 1;
        uint8_t avx512ifma       : 1;
        uint8_t pcommit          : 1;
        uint8_t clflushopt       : 1;
        uint8_t clwb             : 1;
        uint8_t intelproctrace   : 1;
        uint8_t avx512pf         : 1;
        uint8_t avx512er         : 1;
        uint8_t avx512cd         : 1;
        uint8_t sha              : 1;
        uint8_t avx512bw         : 1;
        uint8_t avx512vl         : 1;
      };
      
      uint32_t reg;
      
    } ebx = { .reg = 0 };
    
    union {
      struct {
        uint8_t prefetchwt1: 1;
        uint8_t avx512vbmi : 1;
        uint32_t reserved  : 30;
      };
      
      uint32_t reg;
      
    } ecx = { .reg = 0 };

    uint32_t edx = 0;
    uint32_t eax = 7; 
    
    __cpuid(7, eax, ebx.reg, ecx.reg, edx);

    printf("bmi1      :\t%d\n"
	   "avx2      :\t%d\n"
	   "bmi2      :\t%d\n"
	   "avx512f   :\t%d\n"
	   "avx512dq  :\t%d\n"
	   "avx512ifma:\t%d\n"
	   "avx512pf  :\t%d\n"
	   "avx512er  :\t%d\n"
	   "avx512cd  :\t%d\n"
	   "sha       :\t%d\n"
	   "avx512bw  :\t%d\n"
           "avx512vl  :\t%d\n"
	   "avx512vbmi:\t%d\n",
           ebx.bmi1, ebx.avx2, ebx.bmi2, ebx.avx512f, ebx.avx512dq,
           ebx.avx512ifma, ebx.avx512pf, ebx.avx512er, ebx.avx512cd, ebx.sha,
           ebx.avx512bw, ebx.avx512vl, ecx.avx512vbmi);
  }
  return 0;
}
