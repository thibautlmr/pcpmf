using PricingClient;
using ParameterInfo.RebalancingOracleDescriptions;
using TimeHandler;
namespace FinancialApp
{
    public class ComputationUtilities
    {
        public Pricer Pricer { get; set; }
        public DataUtilities DataUtilities { get; set; }

        public ComputationUtilities(Pricer pricer, DataUtilities dataUtilities)
        {
            Pricer = pricer;
            DataUtilities = dataUtilities;
        }

        public bool RebalancingTime(int t)
        {
            IRebalancingOracleDescription rebalancingOracleDescription = DataUtilities.TestParameters.RebalancingOracleDescription;
            if (rebalancingOracleDescription.Type == RebalancingOracleType.Fixed)
            {
                int period = ((FixedTimesOracleDescription)rebalancingOracleDescription).Period;
                return t % period == 0;
            }
            else
            {
                throw new InvalidDataException("Invalid Rebalancing Description");
            }
        }

        public double GetFreeRateBetweenTwoDates(DateTime date1, DateTime date2)
        {
            string domesticCurrencyId = DataUtilities.TestParameters.AssetDescription.DomesticCurrencyId;
            double annualFreeRate = DataUtilities.TestParameters.AssetDescription.CurrencyRates[domesticCurrencyId];
            int numberOfDaysInOneYear = DataUtilities.TestParameters.NumberOfDaysInOneYear;
            MathDateConverter mathDateConverter = new(numberOfDaysInOneYear);
            double elapsedTime = mathDateConverter.ConvertToMathDistance(date1, date2);
            return annualFreeRate * elapsedTime / numberOfDaysInOneYear;
        }

        public double[] GetDeltas()
        {
            return Pricer.Deltas.ToArray();
        }

        public double[] GetDeltaStdDev()
        {
            return Pricer.DeltasStdDev.ToArray();

        }

        public double GetPrice()
        {
            return Pricer.Price;
        }

        public double GetPriceStdDev()
        {
            return Pricer.PriceStdDev;
        }

        public bool IsMonitoringDateReached(DateTime date)
        {
            DateTime[] paymentDates = DataUtilities.TestParameters.PayoffDescription.PaymentDates;
            for (int i = 0; i < paymentDates.Length; i++)
            {
                if (paymentDates[i].Date == date)
                {
                    return true;
                }
            }
            return false;
        }

        public double GetElapsedTime(DateTime date)
        {
            int numberOfDaysInOneYear = DataUtilities.TestParameters.NumberOfDaysInOneYear;
            DateTime firstDate = DataUtilities.MarketData[0].Date;
            MathDateConverter mathDateConverter = new(numberOfDaysInOneYear);
            return mathDateConverter.ConvertToMathDistance(firstDate, date);
        }
    }
}
