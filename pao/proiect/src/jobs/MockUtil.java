package jobs;

import jobs.db.JobDatabase;
import jobs.model.Category;
import jobs.model.Company;
import jobs.model.Job;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Random;

public class MockUtil {
    private final static String[] COMPANY_NAMES = {
            "Bitdefender",
            "Avira",
            "Mega Image",
            "Microsoft",
            "Endava",
            "Google",
            "Facebook",
    };

    private final static String[] JOB_TITLE_PREFIXES = {
            "",
            "Junior",
            "Senior",
            "Remote",
            "Assistant",
            "Manager",
    };

    private final static String[] JOB_TITLES = {
            "Designer",
            "Software Engineer",
            "Store Clerk"
    };

    private final static int NUM_COMPANIES = COMPANY_NAMES.length;
    private final static int NUM_JOBS = 15;


    private MockUtil() {}

    public static void fillDatabaseWithMockData(JobDatabase db, long seed) {
        Random rng = new Random(seed);

        List<Company> companies = new ArrayList<>();

        for (int i = 0; i < NUM_COMPANIES; ++i) {
            String name = COMPANY_NAMES[i];

            int id = generateCompanyId(rng);

            Company company = new Company(name, id);

            companies.add(company);
            db.addCompany(company);
        }

        for (int i = 0; i < NUM_JOBS; ++i) {
            String prefix = JOB_TITLE_PREFIXES[rng.nextInt(JOB_TITLE_PREFIXES.length)];
            String title = JOB_TITLES[rng.nextInt(JOB_TITLES.length)];
            title = prefix + " " + title;

            Date postingDate = new Date();

            Category category = Category.Business;

            Company company = companies.get(rng.nextInt(NUM_COMPANIES));

            Job job = new Job(title, postingDate, category, company);

            db.addJob(job);
        }
    }

    private static int generateCompanyId(Random rng) {
        return 1_000_000 + rng.nextInt(500_000);
    }
}
