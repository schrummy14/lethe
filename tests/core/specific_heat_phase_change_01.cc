/**
 * @brief Tests the specific_heat_phase_change model.
 * The phase change model uses a "mushy" zone approach to model the phase change
 * of a material. This is achieved by distributing the latent heat associated
 * with a phase change over the phase change interval (mushy zone). This
 * interval is defined by [T_solidus,T_liquidus]. This test verifies that the Cp
 * is calculated correctly. For temperature T<T_solidus, the cp should be cp_s.
 * For temperatures T>T_liquidus the Cp should be cp_l. For temperature
 * in-between, T \in [T_solidus,T_liquidus] the Cp should be 0.5(cp_l+cp_s) +
 * latent_enthalpy / (T_liquidus-T_solidus).
 */

// Lethe
#include <core/parameters.h>
#include <core/specific_heat_model.h>

// Tests (with common definitions)
#include <../tests/tests.h>

void
test()
{
  deallog << "Beggining" << std::endl;

  Parameters::PhaseChange phase_change_param;
  phase_change_param.cp_l            = 3;
  phase_change_param.cp_s            = 1;
  phase_change_param.latent_enthalpy = 100;
  phase_change_param.T_solidus       = 1;
  phase_change_param.T_liquidus      = 2;


  PhaseChangeSpecificHeat specific_heat_model(phase_change_param);


  deallog << "Testing solid fraction xi" << std::endl;

  deallog << " T = 0.5  , xi = " << specific_heat_model.liquid_fraction(0.5)
          << std::endl;
  deallog << " T = 1    , xi = " << specific_heat_model.liquid_fraction(1)
          << std::endl;
  deallog << " T = 1.5  , xi = " << specific_heat_model.liquid_fraction(1.5)
          << std::endl;
  deallog << " T = 1.75 , xi = " << specific_heat_model.liquid_fraction(1.75)
          << std::endl;
  deallog << " T = 2    , xi = " << specific_heat_model.liquid_fraction(2)
          << std::endl;
  deallog << " T = 2.5  , xi = " << specific_heat_model.liquid_fraction(2.5)
          << std::endl;


  deallog << "Testing enthalpy H" << std::endl;
  deallog << " T = 0.5  , H = " << specific_heat_model.enthalpy(0.5)
          << std::endl;
  deallog << " T = 1    , H = " << specific_heat_model.enthalpy(1) << std::endl;
  deallog << " T = 1.5  , H = " << specific_heat_model.enthalpy(1.5)
          << std::endl;
  deallog << " T = 2    , H = " << specific_heat_model.enthalpy(2) << std::endl;
  deallog << " T = 2.5  , H = " << specific_heat_model.enthalpy(2.5)
          << std::endl;


  deallog << "Testing specific heat" << std::endl;

  double T_0 = 0.1;
  double dT  = 0.2;
  double T_1 = T_0 + dT;
  for (int i = 0; i < 20; ++i)
    {
      std::map<field, double> field_values;
      field_values[field::temperature]          = T_1;
      field_values[field::previous_temperature] = T_0;

      deallog << " T_0 = " << T_0 << " T_1 = " << T_1
              << " Cp = " << specific_heat_model.value(field_values)
              << std::endl;
      T_0 += dT;
      T_1 += dT;
    }


  deallog << "OK" << std::endl;
}

int
main()
{
  try
    {
      initlog();
      test();
    }
  catch (std::exception &exc)
    {
      std::cerr << std::endl
                << std::endl
                << "----------------------------------------------------"
                << std::endl;
      std::cerr << "Exception on processing: " << std::endl
                << exc.what() << std::endl
                << "Aborting!" << std::endl
                << "----------------------------------------------------"
                << std::endl;
      return 1;
    }
  catch (...)
    {
      std::cerr << std::endl
                << std::endl
                << "----------------------------------------------------"
                << std::endl;
      std::cerr << "Unknown exception!" << std::endl
                << "Aborting!" << std::endl
                << "----------------------------------------------------"
                << std::endl;
      return 1;
    }
}
