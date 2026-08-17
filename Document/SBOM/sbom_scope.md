# MS51_BSP SBOM Scope 說明

本文件說明 MS51_BSP 的 SBOM 範圍劃分，對應 MS00 SBOM 提供政策
（`doc/MS00_SBOM_提供說明.pptx`）與 BSP SBOM 產生指南
（`doc/bsp_sbom_generation_guide.html`）。

## 產品概觀

- BSP 名稱：`MS51_BSP`
- 架構：Nuvoton 8051（1T 8051），非 ARM Cortex-M，故 **無 CMSIS**
- 授權：Apache-2.0（見 BSP root `LICENSE.txt` / `NOTICE.txt`）
- 內含三個晶片家族，每個家族有各自的 `Library/` 與 `SampleCode/`：
  - `MS51DA9AE_MS51BA9AE`
  - `MS51FB9AE_MS51XB9AE_MS51XB9BE`
  - `MS51FC0AE_MS51XC0BE_MS51EB0AE_MS51EC0AE_MS51TC0AE_MS51PC0AE`

## Product SBOM（`product-scope.yaml`）

用途：CRA 合規、產品漏洞管理、客戶產品整合風險評估。

涵蓋每個家族下會被整合進最終韌體的 first-party 執行期原始碼：

| 目錄 | 內容 | 角色 |
| --- | --- | --- |
| `Library/Device` | 裝置暫存器定義、SFR header | Device support |
| `Library/Startup` | IAR / Keil 啟動碼、向量表 | Startup code |
| `Library/StdDriver` | 標準週邊驅動（ADC、GPIO、I2C、PWM…） | Runtime driver |

`bsp:runtime-scope = true`、`bsp:included-in-product-firmware = true`。

## Test Sample SBOM（`test-sample-scope.yaml`）

用途：透明揭露與內部 / 客戶評估，**標示為非產品 runtime dependency**。

涵蓋每個家族下的 `SampleCode/`：

| 目錄 | 內容 |
| --- | --- |
| `SampleCode/RegBased` | 暫存器操作範例（各週邊） |
| `SampleCode/PowerManagement` | Idle / Power-down 範例 |
| `SampleCode/ISP` | ISP（UART0/UART1/I2C）韌體與 `ExcutableBin/` 產物 |
| `SampleCode/Template` | 專案樣板（IAR/Keil/SDCC） |

`bsp:runtime-scope = false`、`bsp:included-in-product-firmware = false`。
除非客戶自行整合，否則不視為產品依賴。

## 不適用項目

MS51_BSP 目前 **沒有** 下列目錄，故 scope 內未列入：

- `Library/CMSIS`（8051 架構不適用）
- `ThirdParty/`、`Tool/`、`Utilities/`（本 BSP 未提供）

若未來新增第三方元件（例如 FatFs、FreeRTOS），應在
`Document/SBOM/components/ProductView/` 或
`Document/SBOM/components/TestSampleView/` 補上 manual SCA JSON，
由 `tools/gen_bsp_sbom.py` 於產生時 merge。
